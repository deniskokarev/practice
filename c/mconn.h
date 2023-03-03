#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
************* Mconn service API ***************
**********************************************/

/**
 * mconn_service class sends a payload enveloped with AppID and MsgType header.
 *
 * You most likely will be using a higher-level RPC service with Protobuf serialization,
 * but just in case if you want to make a non-PB service or wonder what foundation
 * RPC is standing on, here is the basic mconn_service definition.
 *
 * Each service will be derived from mconn_service and must be aware of src data format
 * as well as how to serialize the payload. That is the service has a notion of internal
 * record representaion as well as method of serializing them.
 */
typedef struct mconn_service_s mconn_service_t;

typedef enum mconn_error_e {
    MCONN_OK = 0,
    MCONN_ERR_NOT_READY = -1,
    MCONN_ERR_FULL = -2,
    MCONN_ERR_SERIALIZE = -3,
    MCONN_ERR_SEND = -4,
    MCONN_ERR_MSG_PARSE = -5,
    MCONN_ERR_MSG_UNKNOWN = -6,
} mconn_error_t;

/**
 * Each transmission will be accompanied with the status callback and a param given
 * at mconn_register_on_transmit_cb() registration
 * \see mconn_register_on_transmit_cb()
 * \arg status - MCONN_OK on success or error code
 * \arg param - param provided at registration
 */
typedef void (*mconn_on_transmit_cb)(mconn_error_t status, void* param);

/**
 * The user must register tx callback before sending attempts
 * \arg svc - service to be used for transmission
 * \arg tx_cb - a callback that will be triggered on transmission
 */
void mconn_register_on_transmit_cb(mconn_service_t* svc, mconn_on_transmit_cb tx_cb);

/**
 * Send a record by using serivce data serializer for the given `record`,
 * \see mconn_register_serializer(),
 * enveloped with [AppId,MsgType,Size] header. Then transmit and invoke registred callback.
 * \see mconn_register_on_transmit_cb()
 * \arg svc - a provided service
 * \arg record - a record to transmit
 * \arg param - optional param to be given to the tx callback, for example to identify the
 * transaction the status will be provided in async fashion via registered mconn_tx callback
 */
void mconn_service_send(mconn_service_t* svc, const void* record, void* param);

/**
 * mconn_handler class identifies a handler for a given AppID and MsgType
 */
typedef struct mconn_handler_s mconn_handler_t;

/**
 * The raw-data receive callback. The data pointer is scoped only to the callback.
 * You can either reply to the received data within the callback using mconn_service_send()
 * or do it later.
 * \arg handler - the handler which received the payload
 * \arg data - pointer to data (without the header)
 * \arg size - data size
 * \arg param - an extra handler parameter given at registration
 * \return MCONN_OK when no errors, otherwise it may be MCONN_ERR_MSG_PARSE on protobuf parsing
 * error, or MCONN_ERR_MSG_UNKNOWN when we're trying to handle an unknown message
 */
typedef mconn_error_t (
        *mconn_handle_fn)(mconn_handler_t* handler, const void* data, size_t size, void* param);

/**
 * It is not expected that users will be handling raw data, but it's possible.
 * \arg handler - which handler to attach to
 * \arg handle_fn - the user function to be executed when message arrives
 * \arg param - an extra parameter given to handler function
 */
void mconn_register_handler(mconn_handler_t* hander, mconn_handle_fn handle_fn, void* param);

/**********************************************
*************** Provided services *************
**********************************************/

// for RPC services look at mconn_rpc.h

/**
 * You can use dev_null service if you want to drop the data
 */
extern mconn_service_t mconn_dev_null_svc;

/**
 * Service that sends a null-terminated string payload to app_id=0, msg_type=0
 * for EMG app testing
 */
// taken by emg_streaming app
// TODO: remove after testing
extern mconn_service_t* mconn_service_emg_test;

/**********************************************
*************** Provided handlers *************
**********************************************/

// for RPC handlers look at mconn_rpc.h

#ifdef __cplusplus
}
#endif
