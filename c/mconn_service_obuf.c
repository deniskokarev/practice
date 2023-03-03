#include <stdatomic.h>
#include <assert.h>
#include <string.h>
#include "mconn_service_obuf.h"

/**
 * One-producer, one-consumer lockless fifo buffer for variable size records.
 * If you have multiple producers they'll have to be sequentialized somehow else.
 */

#ifndef ASSERT
#define ASSERT(X) assert(X)
#endif

/**
 *
 * Lockless 1-producer / 1-consumer algorithm:
 * If we had an infinite buffer buf[] with infinite indexes
 * ------------------------------
 *      ^         ^
 *      H         T
 *
 * where one producer increments T and one consumer increments H,
 * then we just have to support one constraint H <= T in the consumer.
 *
 * When we switch to finite ring buffer size S and infinite
 * indexes (such as uint64), we just have to maintain one more condition in the producer
 * T <= H + S, overall: H <= T <= H + S
 * Buffer is empty when H == T. Buffer is full when T - H == S
 *
 * Both H and T may be observed with their last known values, as it gives the most conservative
 * estimate for both constraints. Taking older value may give only false positives.
 *
 * We can also observe that if the buffer size S is < 2^32 we could just use regular unsigned
 * 32-bit integers for indexes (with some arithmetic care)
 *
 * The logic is simple assuming the consumer "sees" the producer changes in same order:
 *
 * record_t buf[S];
 * unsigned H, T;
 *
 * produce(record) {
 *   unsigned h = H;
 *   if (T - h + 1 <= S) {
 *     buf[h % S] = record;
 *     T++;
 *   } else {
 *     return ERR_FULL;
 *   }
 * }
 *
 * consume() {
 *   for (unsigned t = T; H != t; h++) {
 *     process_record(&buf[H % S]);
 *     H++;
 *   }
 * }
 *
 */

/**
 * The reality is a bit more complicated. The records that we produce/consume are not
 * of equal size. Thus we'll have to have 2 fifo queues. Secondary buffer for byte content
 * and primary buffer for record sizes/offsets and user callbacks. We synchronize on
 * primary record-level queue.
 * Additionally need room for downstream callback params. One downstream transmission
 * corresponds to a range of recs. Once the downstream gives us status on the transmission
 * we invoke all recs callbacks in the range
 */
// How many simultaneous downstream send()s are allowed. BSL claims upto 8.
// 1 means we always wait for bsl callback before next bsl_send().
// Only one bsl_send() at a time seem to demonstrate more
// stable bsl performance. Doesn't seem to reduce the bandwidth compared to 2.
#define CB_PARAM_BUF_SZ 1
// Content buffer must be >= (CB_PARAM_BUF_SZ + 2) * MTU:
// - we keep few in sending state,
// - 1 MTU padding at the end of the buff
// - and expect input record to be as large as 1 MTU
#define BYTE_BUF_SZ (1 << 14)
// Let's assume the average record would be 16 bytes
// it's ok to guess wrong - in that case we may be
// choking on records buffer vs content buffer
#define RECORD_BUF_SZ (BYTE_BUF_SZ / 16)

/**
 * Each record has
 */
typedef struct {
    unsigned ofs;
    unsigned sz;
    mconn_service_t* svc; // NULL means skip record
    void* on_tx_cb_param;
} mconn_fifo_record_t;

/**
 * Records interval for serializer and callback
 */
typedef struct {
    mconn_fifo_t* fifo;
    unsigned id;
    unsigned from;
    unsigned to;
} mconn_fifo_interval_t;

/**
 * We have three fifo queues
 * - bytes: record contents
 * - recs: record sizes/offsets/callbacks
 * - cbparam: arguments for downstream serializer and on_tx callback
 * head == tail - queue empty
 * tail-head == SZ - queue full
 *
 * head and tail are only incremented maintaining
 * H <= T <= H + SZ constraint
 * 1 producer thread increments T, 1 consumer thread increments H.
 * H and T are incremented in atomic fashion to guarantee a memory fence:
 * all memory changes before atomic add are "flushed" and become
 * visible to another thread
 */
struct mconn_fifo_s {
    char bytes[BYTE_BUF_SZ];
    unsigned bytes_head;
    atomic_uint bytes_tail;
    mconn_fifo_record_t recs[RECORD_BUF_SZ];
    unsigned recs_head;
    atomic_uint recs_tail;
    mconn_fifo_interval_t cbparam[CB_PARAM_BUF_SZ];
    unsigned cbparam_head;
    atomic_uint cbparam_tail;
    mconn_fifo_stat_t stat;
    unsigned max_rec_sz; // MTU size is the max record size we allow to enqueue
};

const mconn_fifo_stat_t* mconn_fifo_get_stat(const mconn_fifo_t* me) {
    mconn_fifo_stat_t* ucstat = (mconn_fifo_stat_t*)&me->stat;
    ucstat->dbg.bytes_head = me->bytes_head;
    ucstat->dbg.bytes_tail = me->bytes_tail;
    ucstat->dbg.recs_head = me->recs_head;
    ucstat->dbg.recs_tail = me->recs_tail;
    ucstat->dbg.cbparam_head = me->cbparam_head;
    ucstat->dbg.cbparam_tail = me->cbparam_tail;
    return &me->stat;
}

/**
 * Force-fail all the callbacks in the queue, wipe the content and set new MTU
 * \arg me - this fifo
 * \arg max_rec_sz - new MTU size. The max record in the fifo cannt exceed that
 * Fifo is ready for immediate use after - no need to open()
 * \return MCONN_FULL when max_rec_sz is too large for the fifo buffer, otherwise MCONN_OK
 */
mconn_error_t mconn_fifo_reinit(mconn_fifo_t* me, unsigned max_rec_sz) {
    // we should be able to keep CB_PARAM_BUF_SZ MTUs until on_transmission
    // callbacks fullfilled, plus space for current record, plus space for padding
    // at the end of the buffer
    int enough_room = (BYTE_BUF_SZ >= max_rec_sz * (CB_PARAM_BUF_SZ + 2));
    if (!enough_room) {
        return MCONN_ERR_FULL;
    } else {
        for (unsigned i = me->recs_head; i != me->recs_tail; i++) {
            mconn_fifo_record_t* rec = &me->recs[i % RECORD_BUF_SZ];
            if (rec->svc) {
                rec->svc->on_send(MCONN_ERR_SEND, rec->on_tx_cb_param);
            }
        }
        memset(me, 0, sizeof(*me));
        me->max_rec_sz = max_rec_sz;
        return MCONN_OK;
    }
}

/**
 * Define one static fifo buffer to be used for all
 * mconn_service_obuf_t services on 1 L2CAP channel
 */
mconn_fifo_t mconn_fifo;

/**
 * Check if there is enough room for more elements in the ring buffer size sz
 * head == tail -> buffer empty
 * tail - head == sz -> buffer full
 * @arg head - ring buffer head
 * @arg tail - ring buffer tail
 * @arg sz - ring buffer size
 * @arg more - can we add more elements to the buffer
 * @returns true when there is enough space in the buffer
 */
static int enough_room(unsigned head, unsigned tail, unsigned sz, unsigned more) {
    return tail + more - head <= sz;
}

/**
 * We cannot allow one record content to wrap around the buffer. Otherwise we won't be able to
 * send() the record directly. Since we know the maximum record size is mtu_sz we must
 * pad the and of the buffer with unused record if remaining tail is < mtu_sz
 * @param me
 * @param mtu_sz padding size to maintain at the end of the bytes buffer
 * @param bh the latest known bytes buffer head
 * @param rh the latest known records buffer head
 * @return MCONN_ERR_FULL when we don't have enough room to pad the buffer
 */
static int
mconn_fifo_produce_spacer_if_needed(mconn_fifo_t* me, unsigned mtu_sz, unsigned bh, unsigned rh) {
    size_t till_end = BYTE_BUF_SZ - (me->bytes_tail % BYTE_BUF_SZ);
    if (till_end && till_end < mtu_sz) {
        if (enough_room(bh, me->bytes_tail, BYTE_BUF_SZ, till_end) &&
            enough_room(rh, me->recs_tail, RECORD_BUF_SZ, 1)) {
            unsigned ofs = atomic_fetch_add(&me->bytes_tail, till_end);
            me->recs[me->recs_tail % RECORD_BUF_SZ] =
                    (mconn_fifo_record_t){.ofs = ofs, .sz = till_end, .svc = NULL};
            (void)atomic_fetch_add(&me->recs_tail, 1);
        } else {
            return MCONN_ERR_FULL; // cannot place spacer record
        }
    }
    return MCONN_OK;
}

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
void mconn_obuf_enqeue(mconn_service_obuf_t* me, const void* src, void* on_send_opt) {
    mconn_fifo_t* fifo = me->fifo;
    fifo->stat.records_rx++;
    // get the most conservative remaining space estimate in both buffers, fetch order doesn't matter
    unsigned bh = fifo->bytes_head;
    unsigned rh = fifo->recs_head;
    if (mconn_fifo_produce_spacer_if_needed(fifo, fifo->max_rec_sz, bh, rh) != MCONN_OK) {
        me->super.on_send(MCONN_ERR_FULL, on_send_opt);
        fifo->stat.records_rx_err_full++;
        return;
    }
    if (enough_room(bh, fifo->bytes_tail, BYTE_BUF_SZ, fifo->max_rec_sz) &&
        enough_room(rh, fifo->recs_tail, RECORD_BUF_SZ, 1)) {
        int sz = me->super.serialize(
                &me->super, &fifo->bytes[fifo->bytes_tail % BYTE_BUF_SZ], fifo->max_rec_sz, src);
        if (sz >= 0) {
            unsigned ofs = atomic_fetch_add(&fifo->bytes_tail, sz);
            fifo->recs[fifo->recs_tail % RECORD_BUF_SZ] = (mconn_fifo_record_t){
                    .ofs = ofs, .sz = sz, .svc = &me->super, .on_tx_cb_param = on_send_opt};
            (void)atomic_fetch_add(
                    &fifo->recs_tail, 1); // write fence: consumer thread "sees" all updates before
            fifo->stat.bytes_rx += sz;
        } else {
            me->super.on_send(MCONN_ERR_SERIALIZE, on_send_opt);
            fifo->stat.records_rx_err_serial++;
        }
    } else {
        fifo->stat.records_rx_err_full++;
        me->super.on_send(MCONN_ERR_FULL, on_send_opt);
    }
}

/**
 * The downstream service must use this on_send() callback in order to
 * trigger all callbacks enqueued in the fifo
 * @param status downstream's send status
 * @param opt echoed-back interval that was given by mconn_obuf_ship_one_mtu()
 */
void mconn_obuf_notify_senders(mconn_error_t status, void* opt) {
    mconn_fifo_interval_t* interval = (mconn_fifo_interval_t*)opt;
    mconn_fifo_t* fifo = interval->fifo;
    fifo->stat.downstream_cb++;
    if (status != MCONN_OK) {
        fifo->stat.downstream_cb_err++;
    }
    unsigned cbh = fifo->cbparam_head++;
    ASSERT(interval->id == cbh && "the callbacks must come in order");
    for (unsigned i = interval->from; i != interval->to; i++) {
        mconn_fifo_record_t* rec = &fifo->recs[i % RECORD_BUF_SZ];
        if (rec->svc) {
            rec->svc->on_send(status, rec->on_tx_cb_param);
            fifo->stat.records_tx++;
            fifo->stat.bytes_tx += rec->sz;
            if (status != MCONN_OK) {
                fifo->stat.records_tx_err++;
                fifo->stat.bytes_tx_err += rec->sz;
            }
        }
    }
}

/**
 * The downstream service must use this serializer() in order to
 * ship the set of records from fifo
 * @param svc - will be downstream service that ships data from obuf
 * @param dst - downstream's output buffer
 * @param dst_max_sz - max record size
 * @param src - mconn_fifo_interval_t* that will be given by obuf to send
 * @return populated downstream buffer size - no error expected
 */
int mconn_obuf_serialize_interval(
        const mconn_service_t* svc,
        void* dst,
        size_t dst_max_sz,
        const void* src) {
    mconn_fifo_interval_t* interval = (mconn_fifo_interval_t*)src;
    mconn_fifo_t* fifo = interval->fifo;
    fifo->stat.downstream_mtu_tx++;
    char* out = dst;
    size_t sz = 0;
    for (unsigned i = interval->from; i != interval->to; i++) {
        mconn_fifo_record_t* rec = &fifo->recs[i % RECORD_BUF_SZ];
        if (rec->svc) {
            // we already made sure that the total volume of records in the
            // interval fits into mtu
            sz += rec->sz;
            ASSERT(sz <= dst_max_sz && "the downstream service must accept MTU-size buffer");
            memcpy(out, fifo->bytes + (rec->ofs % BYTE_BUF_SZ), rec->sz);
            out += rec->sz;
        }
    }
    return sz;
}

/**
 * Consumer can use this best guess if the fifo is empty.
 * Returns 1 when there is nothing to ship at the moment.
 */
int mconn_ship_is_empty(mconn_service_ship_t* me) {
    mconn_fifo_t* fifo = me->fifo;
    unsigned rh = fifo->recs_head;
    unsigned rt = fifo->recs_tail;
    return rh == rt;
}

/**
 * Producer can check if the fifo has a room for 1 more record.
 * Return 1 when you can definitely add one more record.
 */
int mconn_obuf_has_room(mconn_service_obuf_t* me) {
    mconn_fifo_t* fifo = me->fifo;
    // expecting one MTU size record and one ~MTU size spacer
    return enough_room(fifo->bytes_head, fifo->bytes_tail, BYTE_BUF_SZ, fifo->max_rec_sz * 2) &&
           enough_room(fifo->recs_head, fifo->recs_tail, RECORD_BUF_SZ, 1);
}

/**
 * Ship one MTU data window via downstream service. No action if there is nothing to ship
 * @param me
 * @return MCONN_ERR_FULL is we're already waiting for CB_PARAM_BUF_SZ on_tx callbacks
 * from downstream service. I.e. trying to ship too fast.
 */
mconn_error_t mconn_ship_one_mtu(mconn_service_ship_t* me) {
    mconn_fifo_t* fifo = me->fifo;
    unsigned cbh = fifo->cbparam_head;
    if (!enough_room(cbh, fifo->cbparam_tail, CB_PARAM_BUF_SZ, 1)) {
        // cannot ship at the moment - we're already waiting for CB_PARAM_BUF_SZ callbacks from
        // downstream
        return MCONN_ERR_FULL;
    }
    // count from..to record numbers to send that'll fit into mtu
    unsigned packet_sz = 0;
    unsigned rt = atomic_load_explicit(&fifo->recs_tail, memory_order_relaxed);
    unsigned rh = fifo->recs_head;
    unsigned bh = fifo->bytes_head;
    int sending = 0;
    while (rh != rt) {
        mconn_fifo_record_t* r = &fifo->recs[rh % RECORD_BUF_SZ];
        if (r->svc) {
            // ignore spacers with svc == NULL
            if (packet_sz + r->sz > fifo->max_rec_sz) {
                // bust
                break;
            }
            sending = 1; // the record size(s) may be 0, but we still need to send them
            packet_sz += r->sz;
        }
        bh += r->sz;
        rh++;
    }
    if (sending) {
        // there is something to send, let's prepare the interval
        fifo->cbparam[fifo->cbparam_tail % CB_PARAM_BUF_SZ] = (mconn_fifo_interval_t){
                .fifo = fifo, .id = fifo->cbparam_tail, .from = fifo->recs_head, .to = rh};
        unsigned cbt = atomic_fetch_add(&fifo->cbparam_tail, 1);
        mconn_service_send(
                &me->super, &fifo->cbparam[cbt % CB_PARAM_BUF_SZ], &fifo->cbparam[cbt % CB_PARAM_BUF_SZ]);
    }
    fifo->bytes_head = bh;
    fifo->recs_head = rh;
    return MCONN_OK;
}
