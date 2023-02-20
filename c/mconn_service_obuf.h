#pragma once

#include <stddef.h>
#include <stdint.h>
#include "mconn_service.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mconn_fifo_s mconn_fifo_t;

void mconn_fifo_reinit(mconn_fifo_t* me);

typedef struct {
    mconn_service_t super;
    mconn_fifo_t *fifo;
    mconn_service_t *downstream;
    int mtu_sz;
} mconn_service_obuf_t;

void mconn_obuf_enqeue(mconn_service_obuf_t* me, void* src, void* on_send_opt);

int mconn_obuf_serialize_interval(
        const mconn_service_t *svc,
        void *out,
        size_t dst_max_sz,
        void *src);

void mconn_obuf_notify_senders(mconn_error_t status, void *opt);

mconn_error_t mconn_obuf_ship_one_mtu(mconn_service_obuf_t *me);

int mconn_obuf_is_empty(mconn_service_obuf_t* me);

int mconn_obuf_has_room(mconn_service_obuf_t* me);

extern mconn_fifo_t *mconn_fifo;

#ifdef __cplusplus
}
#endif
