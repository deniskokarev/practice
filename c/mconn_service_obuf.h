#pragma once

#include <stddef.h>
#include <stdint.h>
#include "mconn_service.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * One-producer, one-consumer lockless fifo buffer for variable size records.
 * If you have multiple producers they'll have to be sequentialized somehow else.
 */
typedef struct mconn_fifo_s mconn_fifo_t;


/**
 * Force-fail all the callbacks still in the queue.
 * Fifo is ready for immediate use after - no need to open()
 */
void mconn_fifo_reinit(mconn_fifo_t* me);

/**
 * Buffered output services will be derivatives of the below
 * where fifo and downstream service will be shared among
 * all services
 */
typedef struct {
    mconn_service_t super;
    mconn_fifo_t *fifo;
    mconn_service_t *downstream;
    int mtu_sz;
} mconn_service_obuf_t;

/**
 * Primary producer function compatible with mconn_service.send()
 * Will serialize the record and store the content into the bytes[] fifo.
 * The content ofs, sz and relative callbacks go into recs[] fifo.
 * The consumption from fifo and sending downstream will be done by
 * mconn_obuf_ship_one_mtu()
 * @param me
 * @param src - source record that has to be serialized by me->serialize()
 * @param on_send_opt - the me->on_send() callback will be invoked with this on_send_opt
 */
void mconn_obuf_enqeue(mconn_service_obuf_t* me, void* src, void* on_send_opt);

/**
 * The downstream service must use this serializer() in order to
 * ship the set of records from fifo
 * @param svc - will be downstream service that ships data from obuf
 * @param dst - downstream's output buffer
 * @param dst_max_sz - max record size
 * @param src - the interval that will be given by obuf to send
 * @return populated downstream buffer size - no error expected
 */
int mconn_obuf_serialize_interval(
        const mconn_service_t *svc,
        void *out,
        size_t dst_max_sz,
        void *src);

/**
 * The downstream service must use this on_send() callback in order to
 * trigger all callbacks enqueued in the fifo
 * @param status downstream's send status
 * @param opt echoed-back interval that was given by mconn_obuf_ship_one_mtu()
 */
void mconn_obuf_notify_senders(mconn_error_t status, void *opt);

/**
 * Ship one MTU data window via downstream service. No action if there is nothing to ship
 * @param me
 * @return MCONN_ERR_FULL is we're already waiting for CB_PARAM_BUF_SZ on_tx callbacks
 * from downstream service. I.e. trying to ship too fast.
 */
mconn_error_t mconn_obuf_ship_one_mtu(mconn_service_obuf_t *me);

/**
 * Consumer can use this best guess if the fifo is empty.
 * Returns 1 when there is nothing to ship at the moment.
 */
int mconn_obuf_is_empty(mconn_service_obuf_t* me);

/**
 * Producer can check if the fifo has a room for 1 more record.
 * Return 1 when you can definitely add one more record.
 */
int mconn_obuf_has_room(mconn_service_obuf_t* me);

/**
 * Define one static fifo buffer to be used for all
 * mconn_service_obuf_t services on 1 L2CAP channel
 */
extern mconn_fifo_t *mconn_fifo;

#ifdef __cplusplus
}
#endif
