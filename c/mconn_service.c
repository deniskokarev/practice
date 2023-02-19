#include "mconn_service.h"

/**
 * The user must register tx callback before sending attempts
 */
void mconn_register_on_transmit_cb(mconn_service_t* svc, mconn_on_transmit_cb tx_cb) {
    svc->on_send = tx_cb;
}

/**
 * Each service must have a serializer. Most services will have serializer initialized
 * at the service struct definition. One can also update a serializer later with this
 * function.
 * \arg svc - service to send the data
 * \arg serializer_fn - custom serializer
 */
void mconn_register_serializer(
        mconn_service_t* svc,
        mconn_service_serialize_payload_fn serializer) {
    svc->serialize = serializer;
}

/**
 * Wether svc->send() is allowed. To be set by server app.
 */
int mconn_service_ready_to_send = 0;

/**
 * Send a record by using serivce data serializer for the given `record`,
 * \see mconn_register_serializer(),
 * enveloped with [AppId,MsgType,Size] header. Then transmit and invoke registred callback.
 * \see mconn_register_on_transmit_cb()
 * \arg svc - a provided service
 * \arg record - a record to transmit
 * \arg param - optional param to be given to the callback, for example to identify the transaction
 * the status will be provided in async fashion via registered mconn_tx callback
 */
void mconn_service_send(mconn_service_t* svc, const void* record, void* param) {
    if (mconn_service_ready_to_send) {
        svc->send(svc, record, param);
    } else {
        svc->on_send(MCONN_ERR_NOT_READY, param);
    }
}

/******************* /dev/null service ***********************/

static int
serialize_not_implemented(const mconn_service_t* svc, void* dst, size_t dst_max_sz, void* src) {
    return MCONN_ERR_SERIALIZE;
}

static void send_not_ready(mconn_service_t* me, const void* src, void* on_send_opt) {
    me->on_send(MCONN_ERR_NOT_READY, on_send_opt);
}

static void on_send_ignore(mconn_error_t status, void* opt) {}

static mconn_service_t null_svc = {
        .app_id = 0,
        .msg_type = 0,
        .serialize = serialize_not_implemented,
        .send = send_not_ready,
        .on_send = on_send_ignore};

mconn_service_t* mconn_service_dev_null = &null_svc;
