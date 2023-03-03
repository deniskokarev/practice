#include <gtest/gtest.h>
#include <thread>
#include <string>
#include <deque>
#include "mconn_service_obuf.h"

/**
 * compute hash function for a sequence of bytes
 */
struct hash_t {
    static constexpr unsigned BASE = 13;

    unsigned x{0};

    void operator+=(char c) {
        x *= BASE;
        x += (unsigned char)c;
    }

    void operator+=(const char* s) {
        while (*s) {
            this->operator+=(*s++);
        }
    }

    operator unsigned() const {
        return x;
    }
};

static constexpr unsigned MTU = 1024;

// init fifo once before all tests
static auto init_fifo = mconn_fifo_reinit(&mconn_fifo, MTU);

/**
 * Each test will be collecting the following counters
 */
struct stat_t {
    uint64_t prod_cnt{};
    uint64_t prod_bytes{};
    hash_t prod_hash{};
    uint64_t prod_cb_cnt{};
    uint64_t prod_cb_bytes{};
    uint64_t prod_cb_err{};
    hash_t prod_cb_hash{};
    uint64_t cons_mtu_cnt{};
    uint64_t cons_bytes{};
    hash_t cons_hash{};
};

// we need to delay the downstream callbacks
// for better simulation
struct downstream_callback_qel_t {
    uint64_t id;
    mconn_error_e status;
    void* on_send_opt;
    void on_send(mconn_service_t* svc) {
        svc->on_send(status, on_send_opt);
    }
};

/**
 * Test consumer to take the input from fifo
 * It'll invoke callbacks and update stats
 */
typedef struct {
    mconn_service_ship_t super;
    stat_t* stat;
    // delay the downstream callbacks using the queue
    std::deque<downstream_callback_qel_t>* dcbq;
} mconn_service_consumer_t;

/**
 * Test consumer just calculates the hash and updates the stats
 * @param me
 * @param src
 * @param on_send_opt
 */
static void consume_calc_hash(mconn_service_consumer_t* me, void* src, void* on_send_opt) {
    char buf[MTU];
    int sz = me->super.super.serialize(&me->super.super, buf, sizeof(buf), src);
    if (sz >= 0) {
        for (int i = 0; i < sz; i++) {
            me->stat->cons_hash += buf[i];
        }
        me->dcbq->push_back((downstream_callback_qel_t){
                .id = me->stat->cons_mtu_cnt, .status = MCONN_OK, .on_send_opt = on_send_opt});
        me->stat->cons_bytes += sz;
        me->stat->cons_mtu_cnt++;
    } else {
        me->dcbq->push_back((downstream_callback_qel_t){
                .id = me->stat->cons_mtu_cnt, .status = MCONN_ERR_SERIALIZE, .on_send_opt = on_send_opt});
    }
    // since our downstream callbacks are still synchroneous with sending
    // must delay by no more than CB_PARAM_BUF_SZ == 1 - 1 = 0 step
    // TODO: implement async callbacks via dedicated thread
    if (!me->dcbq->empty() && me->stat->cons_mtu_cnt > 0) {
        me->dcbq->front().on_send((mconn_service_t*)me);
        me->dcbq->pop_front();
    }
}

static std::deque<downstream_callback_qel_t> dcbq;

/**
 * Test consumer can be created once and reused between tests, except stat has to be cleaned up
 */
static mconn_service_consumer_t consumer_svc = {
        .super =
                {
                        .super =
                                {
                                        .serialize = mconn_obuf_serialize_interval, // serializing input from obuf
                                        .send = (mconn_service_send_fn)consume_calc_hash, // calculate cons_hash
                                        .on_send = mconn_obuf_notify_senders // notify obuf senders
                                },
                        .fifo = &mconn_fifo, // underlying fifo
                },
        .stat = NULL,
        .dcbq = &dcbq,
};

/**
 * Our test fifo producer will be getting regular strings
 * @param svc
 * @param dst
 * @param dst_max_sz
 * @param src
 * @return
 */
static int producer_serialize_string(
        const mconn_service_t* svc,
        void* dst,
        size_t dst_max_sz,
        const void* src) {
    char* str = (char*)src;
    size_t sz = strlen(str);
    if (dst_max_sz < sz) {
        return MCONN_ERR_FULL;
    }
    memcpy(dst, src, sz); // don't ship \0
    return sz;
}

/**
 * We need to test the producer callbacks invoked by test consumer
 * This will be a callback param
 */
struct producer_on_send_t {
    stat_t* stat;
    char* s;
};

/**
 * Producer callback to be updating cb stats
 * @param status
 * @param param
 */
static void producer_on_tx(mconn_error_t status, void* param) {
    producer_on_send_t* arg = static_cast<producer_on_send_t*>(param);
    arg->stat->prod_cb_cnt++;
    if (status != MCONN_OK) {
        arg->stat->prod_cb_err++;
    }
    arg->stat->prod_cb_hash += arg->s;
    arg->stat->prod_cb_bytes += strlen(arg->s);
    free(arg->s);
    free(arg);
}

/**
 * Test buffered service. Ready to be used immediately
 * and may be reused between tests.
 */
static mconn_service_obuf_t producer_svc = {
        .super =
                {
                        .serialize = producer_serialize_string, // this is input data format
                        .send = (mconn_service_send_fn)mconn_obuf_enqeue,
                        .on_send = producer_on_tx, // calculate callback stats
                },
        .fifo = &mconn_fifo, // underlying fifo
};

/**
 * Send so many fixed-size strings into buffered service.
 * @param obuf_svc
 * @param s
 * @param stat
 * @param n
 * @return
 */
static size_t produce_n(mconn_service_obuf_t* obuf_svc, const char* s, stat_t* stat, int n) {
    size_t sz = 0;
    while (n--) {
        producer_on_send_t* on_send_arg =
                static_cast<producer_on_send_t*>(calloc(sizeof(producer_on_send_t), 1));
        on_send_arg->stat = stat;
        on_send_arg->s = strdup(s);
        mconn_service_send(&obuf_svc->super, s, on_send_arg);
        stat->prod_hash += s;
        stat->prod_cnt++;
        size_t l = strlen(s);
        stat->prod_bytes += l;
        sz += l;
    }
    return sz;
}

/**
 * Generate random string size upto max_len
 * @param mx_len
 * @return
 */
std::string rand_str(int mx_len) {
    static auto randchar = []() -> char {
        const static char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    int l = rand() % mx_len;
    std::string res(l, ' ');
    std::generate(begin(res), end(res), randchar);
    return res;
}

/**
 * Send so many random strings into the buffered service to fit within one MTU
 * @param obuf_svc
 * @param stat
 * @param mtu
 * @return
 */
static size_t produce_rand_to_fill_mtu(mconn_service_obuf_t* obuf_svc, stat_t* stat, unsigned mtu) {
    unsigned sz = 0;
    while (true) {
        std::string str = rand_str(31);
        if (sz + str.size() > mtu) {
            break;
        }
        sz += str.size();
        const char* s = str.c_str();
        producer_on_send_t* on_send_arg =
                static_cast<producer_on_send_t*>(calloc(sizeof(producer_on_send_t), 1));
        on_send_arg->stat = stat;
        on_send_arg->s = strdup(s);
        mconn_service_send(&obuf_svc->super, s, on_send_arg);
        stat->prod_hash += s;
        stat->prod_cnt++;
        stat->prod_bytes += strlen(s);
    }
    return sz;
}

/**
 * Consume few MTUs and redirect the data from buffer to downstream service
 * @param obuf_svc
 * @param m
 */
static void consume_m(mconn_service_ship_t* svc, int m) {
    while (m--) {
        mconn_ship_one_mtu(svc);
    }
    while (!consumer_svc.dcbq->empty()) {
        consumer_svc.dcbq->front().on_send((mconn_service_t*)&consumer_svc);
        consumer_svc.dcbq->pop_front();
    }
}

static void assert_fifo_stats(const mconn_fifo_stat_t* stat) {
    ASSERT_EQ(stat->records_rx, stat->records_tx);
    ASSERT_EQ(stat->records_rx_err_full, 0U);
    ASSERT_EQ(stat->records_rx_err_serial, 0U);
    ASSERT_EQ(stat->bytes_rx, stat->bytes_tx);
    ASSERT_EQ(stat->bytes_tx_err, 0U);
    ASSERT_EQ(stat->downstream_mtu_tx, stat->downstream_cb);
    ASSERT_EQ(stat->downstream_cb_err, 0U);
}

/**
 * Perform sequential produce/consume cycles
 * Each cycle is populating and consuming one MTU
 */
struct produce_consume_sequential_t {
    mconn_service_obuf_t& obuf_svc;
    mconn_service_ship_t& ship_svc;
    stat_t stat;

    // produce upto MTU
    produce_consume_sequential_t(mconn_service_obuf_t& o, mconn_service_ship_t& s) : obuf_svc{o}, ship_svc{s}, stat{} {}

    virtual size_t produce_mtu() = 0;

    void operator()(unsigned cycles) {
        consumer_svc.stat = &stat;
        mconn_service_ready_to_send = 1;
        size_t sz = 0;
        for (unsigned i = 0; i < cycles; i++) {
            sz += produce_mtu();
            consume_m(&ship_svc, 1);
        }
        ASSERT_EQ(stat.prod_hash, stat.cons_hash);
        ASSERT_EQ(stat.prod_hash, stat.prod_cb_hash);
        ASSERT_EQ(stat.prod_bytes, sz);
        ASSERT_EQ(stat.prod_bytes, stat.cons_bytes);
        ASSERT_EQ(stat.prod_bytes, stat.prod_cb_bytes);
        ASSERT_EQ(stat.prod_cnt, stat.prod_cb_cnt);
        ASSERT_EQ(stat.prod_cb_err, 0U);
        ASSERT_EQ(stat.cons_mtu_cnt, cycles);
        assert_fifo_stats(mconn_fifo_get_stat(obuf_svc.fifo));
    }
};

/**
 * Produce one fixes string and consume it
 */
struct produce_consume_one_hello_t : produce_consume_sequential_t {
    using produce_consume_sequential_t::produce_consume_sequential_t;

    size_t produce_mtu() override {
        static constexpr char s[] = "hello, world ";
        return produce_n(&obuf_svc, s, &stat, 1);
    }
};

/*************************************************************
 *********************** Sequential *************************
 ************************************************************/
TEST(Sequential, ProduceOnceConsumeOnce) {
    produce_consume_one_hello_t test(producer_svc, consumer_svc.super);
    test(1);
}

/**
 * Produce a batch of fixes string to fill MTU and consume it
 */
struct produce_consume_mtu_filled_hello_t : produce_consume_sequential_t {
    using produce_consume_sequential_t::produce_consume_sequential_t;

    size_t produce_mtu() override {
        static constexpr char s[] = "hello, world ";
        int filln = MTU / strlen(s); // cover almost entire MTU
        return produce_n(&obuf_svc, s, &stat, filln);
    }
};

TEST(Sequential, ProduceFewConsumeOnce) {
    produce_consume_mtu_filled_hello_t test(producer_svc, consumer_svc.super);
    test(1);
}

TEST(Sequential, ProduceFewConsumeFew) {
    produce_consume_mtu_filled_hello_t test(producer_svc, consumer_svc.super);
    test(13);
}

TEST(Sequential, ProduceManyConsumeMany) {
    produce_consume_mtu_filled_hello_t test(producer_svc, consumer_svc.super);
    test(10'000);
}

struct produce_consume_mtu_rand_t : produce_consume_sequential_t {
    using produce_consume_sequential_t::produce_consume_sequential_t;

    size_t produce_mtu() override {
        return produce_rand_to_fill_mtu(&producer_svc, &stat, MTU);
    }
};

TEST(Sequential, ProduceRandManyConsumeMany) {
    produce_consume_mtu_rand_t test(producer_svc, consumer_svc.super);
    test(10'000);
}

/*************************************************************
 ************************* Parallel **************************
 ************************************************************/

struct done_produce_t {
    volatile bool done{};
};

static void run_produce_rand_records(
        mconn_service_obuf_t* obuf_svc,
        stat_t* stat,
        int n,
        done_produce_t* done) {
    while (n) {
        if (mconn_obuf_has_room(obuf_svc)) {
            std::string str = rand_str(31);
            const char* s = str.c_str();
            producer_on_send_t* on_send_arg =
                    static_cast<producer_on_send_t*>(calloc(sizeof(producer_on_send_t), 1));
            on_send_arg->stat = stat;
            on_send_arg->s = strdup(s);
            mconn_service_send(&obuf_svc->super, s, on_send_arg);
            stat->prod_hash += s;
            stat->prod_cnt++;
            stat->prod_bytes += strlen(s);
            n--;
        } else {
            std::this_thread::yield(); // busy wait
        }
    }
    done->done = true;
}

static bool is_done(done_produce_t* done) {
    return done->done;
}

static void run_consume(mconn_service_ship_t* obuf_svc, done_produce_t* done) {
    while (!is_done(done)) {
        if (!mconn_ship_is_empty(obuf_svc)) {
            mconn_ship_one_mtu(obuf_svc);
        } else {
            std::this_thread::yield(); // busy wait
        }
    }
    while (!mconn_ship_is_empty(obuf_svc)) {
        mconn_ship_one_mtu(obuf_svc);
    }
    while (!consumer_svc.dcbq->empty()) {
        consumer_svc.dcbq->front().on_send((mconn_service_t*)&consumer_svc);
        consumer_svc.dcbq->pop_front();
    }
}

static void parallel_test(int records) {
    stat_t stat;
    consumer_svc.stat = &stat;
    mconn_service_ready_to_send = 1;
    done_produce_t done;
    std::thread p(run_produce_rand_records, &producer_svc, &stat, records, &done);
    std::thread c(run_consume, &consumer_svc.super, &done);
    p.join();
    c.join();
    ASSERT_EQ(stat.prod_hash, stat.cons_hash);
    ASSERT_EQ(stat.prod_hash, stat.prod_cb_hash);
    ASSERT_EQ(stat.prod_bytes, stat.cons_bytes);
    ASSERT_EQ(stat.prod_bytes, stat.prod_cb_bytes);
    ASSERT_EQ(stat.prod_cb_err, 0U);
    ASSERT_EQ(stat.prod_cnt, stat.prod_cb_cnt);
    assert_fifo_stats(mconn_fifo_get_stat(producer_svc.fifo));
}

TEST(Parallel, Once) {
    parallel_test(1);
}

TEST(Parallel, Few) {
    parallel_test(13);
}

TEST(Parallel, Many) {
    parallel_test(1'000'000);
}

TEST(Parallel, ALot) {
    parallel_test(10'000'000);
}
