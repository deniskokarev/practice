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
 * Force-fail all the callbacks in the queue, wipe the content and set new MTU
 * \arg me - this fifo
 * \arg max_rec_sz - new MTU size. The max record in the fifo cannt exceed that
 * Fifo is ready for immediate use after - no need to open()
 * \return MCONN_FULL when max_rec_sz is too large for the fifo buffer, otherwise MCONN_OK
 */
mconn_error_t mconn_fifo_reinit(mconn_fifo_t* me, unsigned max_rec_sz);

/**
 * Fifo queue stats. rx (received) and tx (transmitted) is from fifo
 * prospective. The values will fluctuate when fifo is in active use.
 */
typedef struct {
    // rx populated by mconn_obuf_enqeue
    uint64_t records_rx; // all send attemts, including errors
    uint64_t records_rx_err_full; // when buffer was full
    uint64_t records_rx_err_serial; // when user serialiser failed
    uint64_t bytes_rx; // successfully taken bytes
    // tx populated by downstream callbacks, i.e. when records
    // are definitely transmitted or failed to transmit
    uint64_t records_tx; // all transmitted, including errors
    uint64_t records_tx_err; // when downstream error occurred
    uint64_t bytes_tx;
    uint64_t bytes_tx_err; // when downstream error occurred
    // how many MTUs shipped downstream
    uint64_t downstream_mtu_tx;
    // and how many downstream callbacks received
    uint64_t downstream_cb; // all callbacks including errors
    uint64_t downstream_cb_err;
    // snapshot of head/tails for debug
    // TODO: remove after tuneup
    struct {
        uint64_t bytes_head;
        uint64_t bytes_tail;
        uint64_t recs_head;
        uint64_t recs_tail;
        uint64_t cbparam_head;
        uint64_t cbparam_tail;
    } dbg;
} mconn_fifo_stat_t;

const mconn_fifo_stat_t* mconn_fifo_get_stat(const mconn_fifo_t* me);

/**
 * There may be many buffered output services for one fifo
 * all appending records to the same fifo
 */
typedef struct {
    mconn_service_t super;
    mconn_fifo_t* fifo;
} mconn_service_obuf_t;

/**
 * The service to send the fifo data downstream. There will be only
 * one downstream service per fifo
 */
typedef struct {
    mconn_service_t super;
    mconn_fifo_t* fifo;
} mconn_service_ship_t;

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
void mconn_obuf_enqeue(mconn_service_obuf_t* me, const void* src, void* on_send_opt);

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
        const mconn_service_t* svc,
        void* out,
        size_t dst_max_sz,
        const void* src);

/**
 * The downstream service must use this on_send() callback in order to
 * trigger all callbacks enqueued in the fifo
 * @param status downstream's send status
 * @param opt echoed-back interval that was given by mconn_obuf_ship_one_mtu()
 */
void mconn_obuf_notify_senders(mconn_error_t status, void* opt);

/**
 * Ship one MTU data window via downstream service. No action if there is nothing to ship
 * @param me
 * @return MCONN_ERR_FULL is we're already waiting for CB_PARAM_BUF_SZ on_tx callbacks
 * from downstream service. I.e. trying to ship too fast.
 */
mconn_error_t mconn_ship_one_mtu(mconn_service_ship_t* me);

/**
 * Consumer can use this best guess if the fifo is empty.
 * Returns 1 when there is nothing to ship at the moment.
 */
int mconn_ship_is_empty(mconn_service_ship_t* me);

/**
 * Producer can check if the fifo has a room for 1 more record.
 * Return 1 when you can definitely add one more record.
 */
int mconn_obuf_has_room(mconn_service_obuf_t* me);

/**
 * Define one static fifo buffer to be used for all
 * mconn_service_obuf_t services on 1 L2CAP channel
 */
extern mconn_fifo_t mconn_fifo;

#ifdef __cplusplus
}
#endif
