#include <gtest/gtest.h>
#include <thread>
#include <string>
#include "mconn_service_obuf.h"


struct hash_t {
    static constexpr unsigned BASE = 13;

    unsigned x{0};

    void operator+=(char c) {
        x *= BASE;
        x += (unsigned char) c;
    }

    void operator+=(const char *s) {
        while (*s) {
            this->operator+=(*s++);
        }
    }

    operator unsigned() const {
        return x;
    }
};

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

typedef struct {
    mconn_service_t super;
    stat_t *stat;
} mconn_service_consumer_t;

// just calculate the output hash and invoke the callbacks with OK
static void consume_calc_hash(mconn_service_consumer_t *me, void *src, void *on_send_opt) {
    char buf[16 * 1024]; // >= MTU, but fit into stack
    int sz = me->super.serialize(&me->super, buf, sizeof(buf), src);
    if (sz < 0) {
        me->super.on_send((mconn_error_e) sz, on_send_opt);
    } else {
        for (int i = 0; i < sz; i++) {
            me->stat->cons_hash += buf[i];
        }
        me->stat->cons_bytes += sz;
        me->stat->cons_mtu_cnt++;
        me->super.on_send(MCONN_OK, on_send_opt);
    }
}

// can be created once and shared between tests, except stat has to be cleaned up
static mconn_service_consumer_t consumer_svc = {
        .super = {
                .serialize = mconn_obuf_serialize_interval, // serializing input from obuf
                .send = (mconn_service_send_fn) consume_calc_hash, // calculate cons_hash
                .on_send = mconn_obuf_notify_senders // notify obuf senders
        },
        .stat = NULL,
};

static int producer_serialize_string(const mconn_service_t *svc, void *dst, size_t dst_max_sz, void *src) {
    char *str = (char *) src;
    size_t sz = strlen(str);
    if (dst_max_sz < sz) {
        return MCONN_ERR_FULL;
    }
    memcpy(dst, src, sz); // don't ship \0
    return sz;
}

struct producer_on_send_t {
    stat_t *stat;
    char *s;
};

static void producer_on_tx(mconn_error_t status, void *param) {
    producer_on_send_t *arg = (producer_on_send_t *) param;
    arg->stat->prod_cb_cnt++;
    if (status != MCONN_OK) {
        arg->stat->prod_cb_err++;
    }
    arg->stat->prod_cb_hash += arg->s;
    arg->stat->prod_cb_bytes += strlen(arg->s);
    free(arg->s);
    free(arg);
}

// can be created once and shared between tests, except fifo has to be closed
static mconn_service_obuf_t producer_svc = {
        .super = {
                .serialize = producer_serialize_string,
                .send = (mconn_service_send_fn) mconn_obuf_enqeue,
                .on_send = producer_on_tx,
        },
        .fifo = mconn_fifo,
        .out = (mconn_service_t *) &consumer_svc,
        .mtu_sz = 1024,
};

static size_t produce_n(mconn_service_obuf_t *obuf_svc, const char *s, stat_t *stat, int n) {
    size_t sz = 0;
    while (n--) {
        producer_on_send_t *on_send_arg = (producer_on_send_t *) calloc(sizeof(producer_on_send_t), 1);
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
    std::generate_n(begin(res), l, randchar);
    return res;
}

static size_t produce_rand_to_fill_mtu(mconn_service_obuf_t *obuf_svc, stat_t *stat, int mtu) {
    int sz = 0;
    while (true) {
        std::string str = rand_str(31);
        if (sz + str.size() > mtu) {
            break;
        }
        sz += str.size();
        const char *s = str.c_str();
        producer_on_send_t *on_send_arg = (producer_on_send_t *) calloc(sizeof(producer_on_send_t), 1);
        on_send_arg->stat = stat;
        on_send_arg->s = strdup(s);
        mconn_service_send(&obuf_svc->super, s, on_send_arg);
        stat->prod_hash += s;
        stat->prod_cnt++;
        stat->prod_bytes += strlen(s);
    }
    return sz;
}

// redirects from obuf to consumer_svc
static void consume_m(mconn_service_obuf_t *obuf_svc, int m) {
    while (m--) {
        mconn_obuf_ship_one_mtu(obuf_svc);
    }
}

/**
 * Perform sequential produce/consume cycles
 * Each cycle is populating and consuming one MTU
 */
struct produce_consume_sequential_t {
    mconn_service_obuf_t &obuf_svc;
    stat_t stat;

    // produce upto MTU
    produce_consume_sequential_t(mconn_service_obuf_t &s) : obuf_svc{s}, stat {} {}

    virtual size_t produce_mtu() = 0;

    void operator()(int cycles) {
        consumer_svc.stat = &stat;
        mconn_service_ready_to_send = 1;
        size_t sz = 0;
        for (int i = 0; i < cycles; i++) {
            sz += produce_mtu();
            consume_m(&obuf_svc, 1);
        }
        ASSERT_EQ(stat.prod_hash, stat.cons_hash);
        ASSERT_EQ(stat.prod_hash, stat.prod_cb_hash);
        ASSERT_EQ(stat.prod_bytes, sz);
        ASSERT_EQ(stat.prod_bytes, stat.cons_bytes);
        ASSERT_EQ(stat.prod_bytes, stat.prod_cb_bytes);
        ASSERT_EQ(stat.cons_mtu_cnt, cycles);
    }
};

struct produce_consume_one_hello_t: produce_consume_sequential_t {
    using produce_consume_sequential_t::produce_consume_sequential_t;
    size_t produce_mtu() {
        static constexpr char s[] = "hello, world ";
        return produce_n(&obuf_svc, s, &stat, 1);
    }
};

TEST(Sequential, ProduceOnceConsumeOnce) {
    produce_consume_one_hello_t test(producer_svc);
    test(1);
}

struct produce_consume_mtu_filled_hello_t: produce_consume_sequential_t {
    using produce_consume_sequential_t::produce_consume_sequential_t;
    size_t produce_mtu() {
        static constexpr char s[] = "hello, world ";
        int filln = obuf_svc.mtu_sz / strlen(s); // cover almost entire MTU
        return produce_n(&obuf_svc, s, &stat, filln);
    }
};

TEST(Sequential, ProduceFewConsumeOnce) {
    produce_consume_mtu_filled_hello_t test(producer_svc);
    test(1);
}

TEST(Sequential, ProduceFewConsumeFew) {
    produce_consume_mtu_filled_hello_t test(producer_svc);
    test(13);
}

TEST(Sequential, ProduceManyConsumeMany) {
    produce_consume_mtu_filled_hello_t test(producer_svc);
    test(10'000);
}

struct produce_consume_mtu_rand_t: produce_consume_sequential_t {
    using produce_consume_sequential_t::produce_consume_sequential_t;
    size_t produce_mtu() {
        return produce_rand_to_fill_mtu(&producer_svc, &stat, obuf_svc.mtu_sz);
    }
};

TEST(Sequential, ProduceRandManyConsumeMany) {
    produce_consume_mtu_rand_t test(producer_svc);
    test(10'000);
}

struct done_produce_t {
    std::mutex mx{};
    bool done{};
};

static void run_produce_rand_records(mconn_service_obuf_t *obuf_svc, stat_t *stat, int n, done_produce_t *done) {
    while (n) {
        if (mconn_obuf_has_room(obuf_svc)) {
            std::string str = rand_str(31);
            const char *s = str.c_str();
            producer_on_send_t *on_send_arg = (producer_on_send_t *) calloc(sizeof(producer_on_send_t), 1);
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
    {
        std::lock_guard<std::mutex> lk{done->mx};
        done->done = true;
    }
}

static bool is_done(done_produce_t *done) {
    std::lock_guard<std::mutex> lk{done->mx};
    return done->done;
}

static void run_consume(mconn_service_obuf_t *obuf_svc, stat_t *stat, done_produce_t *done) {
    while (!is_done(done)) {
        if (!mconn_obuf_is_empty(obuf_svc)) {
            mconn_obuf_ship_one_mtu(obuf_svc);
        } else {
            std::this_thread::yield(); // busy wait
        }
    }
    while (!mconn_obuf_is_empty(obuf_svc)) {
        mconn_obuf_ship_one_mtu(obuf_svc);
    }
}

static void parallel_test(int records) {
    stat_t stat{};
    consumer_svc.stat = &stat;
    mconn_service_ready_to_send = 1;
    done_produce_t is_done;
    std::thread p(run_produce_rand_records, &producer_svc, &stat, records, &is_done);
    std::thread c(run_consume, &producer_svc, &stat, &is_done);
    p.join();
    c.join();
    ASSERT_EQ(stat.prod_bytes, stat.cons_bytes);
    ASSERT_EQ(stat.prod_bytes, stat.prod_cb_bytes);
    //ASSERT_EQ(stat.prod_cb_cnt, records);
    ASSERT_EQ(stat.prod_hash, stat.cons_hash);
    ASSERT_EQ(stat.prod_hash, stat.prod_cb_hash);
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

/*

TEST(Parallel, ALot) {
    parallel_test(100'000'000);
}
*/
