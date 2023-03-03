#include "mconn_service.h"

/**
 * The user must register tx callback before sending attempts
 */
void mconn_register_on_transmit_cb(mconn_service_t* svc, mconn_on_transmit_cb tx_cb) {
    svc->on_send = tx_cb;
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
