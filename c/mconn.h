#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 * In the unlikely event that you have to define your own record serialization you can rely on
 * custom serialization hook below.
 *
 * In order to minimize memory consumption and improve performance the service is
 * parameterized by the serializer fn. The serializer will be populating the payload content
 * limited by dst_max_sz bytes. It must never populate more than dst_max_sz bytes and must return
 * the volume populated. If the provided dst buffer is insufficient must return
 * MCONN_ERR_FULL.
 * NB: The sender may retry to serialize into a bigger buffer if MCONN_ERR_FULL
 * happened. I.e the streaming functoin must be idempotent to handle theretry with the same `src`.
 * \arg svc - which service we're serializing, it's meant for internal use
 * \arg dst - byte stream destination
 * \arg dst_max_sz - absolute maximum payload size to populate
 * \arg src - a service-specific structure
 * \return populated payload size or negative value on error
 */
typedef int (*mconn_service_serialize_payload_fn)(
        const mconn_service_t* svc,
        void* dst,
        size_t dst_max_sz,
        void* src);

/**
 * The user must register tx callback before sending attempts
 * \arg svc - service to be used for transmission
 * \arg tx_cb - a callback that will be triggered on transmission
 */
void mconn_register_on_transmit_cb(mconn_service_t* svc, mconn_on_transmit_cb tx_cb);

/**
 * In the unlikely event that you need a custom record serializer you can register one
 * \arg svc - service to send the data
 * \arg serializer_fn - custom serializer
 */
void mconn_register_serializer(mconn_service_t* svc, mconn_service_serialize_payload_fn serializer);

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
void mconn_service_send(mconn_service_t* svc, void* record, void* param);

/**
 * mconn_handler class identifies a handler for a given AppID and MsgType
 */
typedef struct mconn_handler_s mconn_handler_t;

/**
 * The raw-data receive callback. The data pointer is scoped only to the callback.
 * You can either reply to the received data within the callback using mconn_service_send()
 * or do it later.
 * \arg data - pointer to data (without the header)
 * \arg size - data size
 * \arg param - optional parameter provided at registration for flexibility and callbacks reuse
 */
typedef void (*mconn_on_receive_cb)(const void* data, size_t size, void* param);

/**
 * It is not expected that users will be handling raw data, but it's possible.
 * \arg handler - which handler to attach to
 * \arg rx_cb - raw data callback function
 * \arg param - an optional param given to the callback function for flexibility
 */
void mconn_register_on_receive_cb(mconn_handler_t* hander, mconn_on_receive_cb rx_cb, void* param);

/**********************************************
*************** Provided services *************
**********************************************/

// /dev/null service
extern mconn_service_t* mconn_service_dev_null;

/**
 * Service that sends a null-terminated string payload to app_id=0, msg_type=0
 * for EMG app testing
 * TODO: remove after testing
 */
extern mconn_service_t* mconn_service_emg_test;

/**********************************************
*************** Provided handlers *************
**********************************************/

/**
 * Handler that receives plain string payloads to app_id=0, msg_type=0
 * for EMG app testing
 * TODO: remove after testing
 */
extern mconn_handler_t* mconn_handler_emg_test;

#ifdef __cplusplus
}
#endif
