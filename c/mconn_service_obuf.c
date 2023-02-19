#include <stdatomic.h>
#include <assert.h>
#include <memory.h>
#include "mconn_service_obuf.h"

#ifndef ASSERT
#define ASSERT(X)   assert(X)
#endif

/**
 *
 * Lockless 1-producer / 1-consumer algorithm:
 * If we had an infinite buffer buf[] with infinite indiexes
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
 * estimate of both constraints. Taking older value may give only false positives.
 *
 * We can also observe that if the buffer size S is < 2^32 we could just use regular unsigned
 * 32-bit integers for indexes (with some arithmetic care)
 *
 * The logic:
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

// must be >= 3 MTU - we keep 1 MTU padding at the end of the buff
// and expect input record to be as large as 1 MTU
#define BYTE_BUF_SZ (1 << 12)
// let's assume the average record would be 16 bytes
#define RECORD_BUF_SZ (BYTE_BUF_SZ / 16)
// how many simultaneous downstream send()s we're waiting callback for
#define CB_PARAM_BUF_SZ   4

typedef struct {
    unsigned ofs;
    unsigned sz;
    mconn_service_t* svc; // NULL means skip record
    void* on_tx_cb_param;
} mconn_fifo_record_t;

typedef struct {
    mconn_fifo_t *fifo;
    unsigned id;
    unsigned from;
    unsigned to;
} mconn_fifo_interval_t;

// memory buffer represending the fifo
struct mconn_fifo_s {
    char bytes[BYTE_BUF_SZ];
    atomic_uint bytes_head;
    atomic_uint bytes_tail;
    mconn_fifo_record_t recs[RECORD_BUF_SZ];
    atomic_uint recs_head;
    atomic_uint recs_tail;
    mconn_fifo_interval_t cbparam[CB_PARAM_BUF_SZ];
    atomic_uint cbparam_head;
    atomic_uint cbparam_tail;
};

// when we don't expect any more callbacks and
// want to close and start over
void mconn_fifo_close(mconn_fifo_t* me) {
    for (unsigned i = me->recs_head; i != me->recs_tail; i++) {
        mconn_fifo_record_t *rec = &me->recs[i % RECORD_BUF_SZ];
        if (rec->svc) {
            rec->svc->on_send(MCONN_ERR_SEND, rec->on_tx_cb_param);
        }
    }
    memset(me, 0, sizeof(*me));
}

// one output buffer is enough for 1 L2CAP channel
// let's initialize with high values for testing purpose
// to catch errors sooner
static mconn_fifo_t mconn_fifo_def = {
        .bytes_head = UINT32_MAX - 1024,
        .bytes_tail = UINT32_MAX - 1024,
        .recs_head = UINT32_MAX - 1024,
        .recs_tail = UINT32_MAX - 1024,
        .cbparam_head = UINT32_MAX - 1024,
        .cbparam_tail = UINT32_MAX - 1024,
};
mconn_fifo_t *mconn_fifo = &mconn_fifo_def;

/**
 * The reality will be more complicated. The records that we produce/consume are not
 * of equal sizes. Thus we'll have to have 2 fifo queues. Secondary buffer for byte content
 * and primary buffer for record sizes/offsets and user callbacks. We synchronize on
 * primary record-level queue.
 */

// ERR_FULL when there is not enough room to place even a spacer
static int mconn_fifo_produce_spacer_if_needed(mconn_fifo_t *me, unsigned mtu_sz) {
    size_t till_end = BYTE_BUF_SZ - (me->bytes_tail % BYTE_BUF_SZ);
    if (till_end && till_end < mtu_sz) {
        // get the most conservative remaining space estimate in both buffers, fetch order doesn't
        // matter
        unsigned bh = atomic_load_explicit(&me->bytes_head, memory_order_relaxed);
        unsigned rh = atomic_load_explicit(&me->recs_head, memory_order_relaxed);
        if (me->bytes_tail + till_end - bh <= BYTE_BUF_SZ && me->recs_tail + 1 - rh <= RECORD_BUF_SZ) {
            unsigned ofs = atomic_fetch_add(&me->bytes_tail, till_end);
            me->recs[me->recs_tail % RECORD_BUF_SZ] =
                    (mconn_fifo_record_t) {.ofs = ofs, .sz = till_end, .svc = NULL};
            (void) atomic_fetch_add(&me->recs_tail, 1);
        } else {
            return MCONN_ERR_FULL; // cannot place spacer a record
        }
    }
    return MCONN_OK;
}

void mconn_obuf_enqeue(mconn_service_obuf_t *me, void *src, void *on_send_opt) {
    mconn_fifo_t *fifo = me->fifo;
    if (mconn_fifo_produce_spacer_if_needed(fifo, me->mtu_sz) != MCONN_OK) {
        me->super.on_send(MCONN_ERR_FULL, on_send_opt);
        return;
    }
    // get the most conservative remaining space estimate in both buffers, fetch order doesn't matter
    unsigned bh = atomic_load_explicit(&fifo->bytes_head, memory_order_relaxed);
    unsigned rh = atomic_load_explicit(&fifo->recs_head, memory_order_relaxed);
    if (fifo->bytes_tail + me->mtu_sz - bh <= BYTE_BUF_SZ && fifo->recs_tail + 1 - rh <= RECORD_BUF_SZ) {
        int sz = me->super.serialize(&me->super, &fifo->bytes[fifo->bytes_tail % BYTE_BUF_SZ], me->mtu_sz, src);
        if (sz >= 0) {
            unsigned ofs = atomic_fetch_add(&fifo->bytes_tail, sz);
            fifo->recs[fifo->recs_tail % RECORD_BUF_SZ] =
                    (mconn_fifo_record_t) {.ofs = ofs, .sz = sz, .svc = &me->super, .on_tx_cb_param = on_send_opt};
            (void) atomic_fetch_add(&fifo->recs_tail, 1);
        } else {
            me->super.on_send(MCONN_ERR_SERIALIZE, on_send_opt);
        }
    } else {
        me->super.on_send(MCONN_ERR_FULL, on_send_opt);
    }
}

void mconn_obuf_notify_senders(mconn_error_t status, void *opt) {
    mconn_fifo_interval_t *interval = (mconn_fifo_interval_t *) opt;
    mconn_fifo_t *fifo = interval->fifo;
    unsigned cbh = atomic_fetch_add(&fifo->cbparam_head, 1);
    ASSERT(interval->id == cbh && "the callbacks must come in order");
    for (unsigned i = interval->from; i != interval->to; i++) {
        mconn_fifo_record_t *rec = &fifo->recs[i % RECORD_BUF_SZ];
        if (rec->svc) {
            rec->svc->on_send(status, rec->on_tx_cb_param);
        }
    }
}

int mconn_obuf_serialize_interval(
        const mconn_service_t *svc,
        void *dst,
        size_t dst_max_sz,
        void *src) {
    mconn_fifo_interval_t *interval = (mconn_fifo_interval_t *) src;
    mconn_fifo_t *fifo = interval->fifo;
    char *out = dst;
    size_t sz = 0;
    for (unsigned i = interval->from; i != interval->to; i++) {
        mconn_fifo_record_t *rec = &fifo->recs[i % RECORD_BUF_SZ];
        if (rec->svc) {
            // we already made sure that the total volume of records in the
            // interval fits into mtu
            memcpy(out, fifo->bytes + (rec->ofs % BYTE_BUF_SZ), rec->sz);
            out += rec->sz;
            sz += rec->sz;
        }
    }
    return sz;
}

/**
 * best guess if the fifo is empty
 * stable result when all writers are down
 */
int mconn_obuf_is_empty(mconn_service_obuf_t* me) {
    mconn_fifo_t *fifo = me->fifo;
    unsigned cbh = atomic_load_explicit(&fifo->recs_head, memory_order_relaxed);
    unsigned cbt = atomic_load_explicit(&fifo->recs_tail, memory_order_relaxed);
    return cbh == cbt;
}

void mconn_obuf_ship_one_mtu(mconn_service_obuf_t* me) {
    mconn_fifo_t *fifo = me->fifo;
    unsigned cbh = atomic_load_explicit(&fifo->cbparam_head, memory_order_relaxed);
    // could just skip one MTU with warning, but let's make it strict
    ASSERT(fifo->cbparam_tail + 1 - cbh <= CB_PARAM_BUF_SZ && "we must not send faster than BSL can take");
    // count from..to record numbers to send that'll fit into mtu
    unsigned packet_sz = 0;
    unsigned rt = atomic_load_explicit(&fifo->recs_tail, memory_order_relaxed);
    unsigned rh = fifo->recs_head;
    unsigned bh = fifo->recs[rh % RECORD_BUF_SZ].ofs;
    while (rh != rt) {
        mconn_fifo_record_t *r = &fifo->recs[rh % RECORD_BUF_SZ];
        if (r->svc) {
            // ignore spacers with svc == NULL
            if (packet_sz + r->sz > me->mtu_sz) {
                // bust
                break;
            }
            packet_sz += r->sz;
        }
        bh += r->sz;
        rh++;
    }
    if (packet_sz) {
        // there is something to send
        fifo->cbparam[fifo->cbparam_tail % CB_PARAM_BUF_SZ] = (mconn_fifo_interval_t) {
                .fifo = fifo,
                .id = fifo->cbparam_tail,
                .from = fifo->recs_head,
                .to = rh
        };
        unsigned cbt = atomic_fetch_add(&fifo->cbparam_tail, 1);
        mconn_service_send(me->out, &fifo->cbparam[cbt % CB_PARAM_BUF_SZ], &fifo->cbparam[cbt % CB_PARAM_BUF_SZ]);
    }
    atomic_store(&fifo->bytes_head, bh);
    atomic_store(&fifo->recs_head, rh);
}
