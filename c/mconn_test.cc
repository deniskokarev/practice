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
    hash_t prod_hash;
    hash_t prod_cb_hash;
    hash_t cons_hash;
};

typedef struct {
    mconn_service_t super;
    stat_t *stat;
} mconn_service_consumer_t;

// just calculate the output hash and invoke the callbacks with OK
static void consume_calc_hash(const mconn_service_consumer_t *me, void *src, void *on_send_opt) {
    char buf[1024*1024]; // >= MTU
    int sz = me->super.serialize(&me->super, buf, sizeof(buf), src);
    if (sz < 0) {
        me->super.on_send((mconn_error_e) sz, on_send_opt);
    } else {
        for (int i = 0; i < sz; i++) {
            me->stat->cons_hash += buf[i];
        }
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

static int producer_serialize_string(const mconn_service_t* svc, void* dst, size_t dst_max_sz, void* src) {
    char *str = (char*)src;
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

static void producer_on_tx(mconn_error_t status, void* param) {
    producer_on_send_t* arg = (producer_on_send_t*)param;
    arg->stat->prod_cb_hash += arg->s;
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
        .out = (mconn_service_t*)&consumer_svc,
        .mtu_sz = 1024,
};

static void produce_n(mconn_service_obuf_t *obuf_svc, stat_t *stat, int n) {
    char *s = (char*)"hello, world";
    while (n--) {
        producer_on_send_t *on_send_arg = (producer_on_send_t *) calloc(sizeof(producer_on_send_t), 1);
        on_send_arg->stat = stat;
        on_send_arg->s = strdup(s);
        stat->prod_hash += s;
        mconn_service_send(&obuf_svc->super, s, on_send_arg);
    }
}

// redirects from obuf to consumer_svc
static void consume_m(mconn_service_obuf_t *obuf_svc, int m) {
    while (m--) {
        mconn_obuf_ship_one_mtu(obuf_svc);
    }
}

TEST(Sequential, ProduceOnceConsumeOnce) {
    stat_t stat;
    consumer_svc.stat = &stat;
    mconn_service_ready_to_send = 1;
    produce_n(&producer_svc, &stat, 1);
    consume_m(&producer_svc, 1);
    mconn_fifo_close(mconn_fifo);
    ASSERT_EQ(stat.prod_hash, stat.cons_hash);
    ASSERT_EQ(stat.prod_hash, stat.prod_cb_hash);
}

TEST(Sequential, ProduceFewConsumeOnce) {
    stat_t stat;
    consumer_svc.stat = &stat;
    mconn_service_ready_to_send = 1;
    produce_n(&producer_svc, &stat, 10);
    consume_m(&producer_svc, 1);
    mconn_fifo_close(mconn_fifo);
    ASSERT_EQ(stat.prod_hash, stat.cons_hash);
    ASSERT_EQ(stat.prod_hash, stat.prod_cb_hash);
}


