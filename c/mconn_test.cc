#include <gtest/gtest.h>
#include <thread>
#include <string>
#include "mconn_service_obuf.h"

struct hash_t {
    unsigned P{13};
    unsigned x{0};

    void operator+=(char c) {
        x *= P;
        x += (unsigned char) c;
    }

    void operator+=(const char *s) {
        while (*s) {
            x *= P;
            x += (unsigned char) *s;
            s++;
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
} mconn_service_test_output_t;

// just calculate the output hash and invoke the callbacks with OK
static void test_output_send_calc_hash(const mconn_service_test_output_t *me, void *src, void *on_send_opt) {
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

static mconn_service_test_output_t test_out_svc = {
        .super = {
                .serialize = mconn_obuf_serialize_interval, // serializing input from obuf
                .send = (mconn_service_send_fn) test_output_send_calc_hash, // calculate cons_hash
                .on_send = mconn_obuf_notify_senders // notify obuf senders
        },
        .stat = NULL,
};

/**
 * Service that sends a string to app_id=0, msg_type=0
 * for EMG app testing.
 * \arg src is treated as a regular 0-terminated tring. 0 is not sent.
 * TODO: remove after testing
 */
static int test_serialize_string(const mconn_service_t* svc, void* dst, size_t dst_max_sz, void* src) {
    char *str = (char*)src;
    size_t sz = strlen(str);
    if (dst_max_sz < sz) {
        return MCONN_ERR_FULL;
    }
    memcpy(dst, src, sz); // no need to ship \0
    return sz;
}

struct on_send_t {
    stat_t *stat;
    char *s;
};

void test_on_send(mconn_error_t status, void* param) {
    on_send_t* arg = (on_send_t*)param;
    arg->stat->prod_cb_hash += arg->s;
    free(arg->s);
    free(arg);
}

static mconn_service_obuf_t out_buf = {
        .super = {
                .serialize = test_serialize_string,
                .send = (mconn_service_send_fn) mconn_obuf_enqeue,
                .on_send = test_on_send,
        },
        .fifo = mconn_fifo,
        .out = (mconn_service_t*)&test_out_svc,
        .mtu_sz = 1024,
};

void producer1(mconn_service_obuf_t *out, stat_t *stat) {
    char *s = (char*)"hello, world";
    on_send_t *on_send_arg = (on_send_t *)calloc(sizeof(on_send_t), 1);
    on_send_arg->stat = stat;
    on_send_arg->s = strdup(s);
    stat->prod_hash += s;
    mconn_service_send(&out->super, s, on_send_arg);
}

void consumer1(mconn_service_obuf_t *out) {
    mconn_obuf_ship_one_mtu(out);
}

TEST(Sequential, Once) {
    stat_t stat;
    test_out_svc.stat = &stat;
    mconn_service_ready_to_send = 1;
    producer1(&out_buf, &stat);
    consumer1(&out_buf);
    ASSERT_EQ(stat.prod_hash, stat.cons_hash);
    ASSERT_EQ(stat.prod_hash, stat.prod_cb_hash);
    mconn_fifo_close(mconn_fifo);
}

