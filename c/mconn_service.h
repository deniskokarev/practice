#pragma once

#include <stddef.h>
#include <stdint.h>
#include "mconn.h"

/**
 * mconn_service is what sends the payload.
 * Basic mconn_service class sends the data enveloped with AppID and MsgType
 *
 * There will be derived service classes, the base class is effectively:
 *
 * class mconn_service {
 *   const uint8_t app_id;
 *   const uint8_t msg_type;
 *   virtual int serialize(void* dst, size_t dst_max_sz, void* src) = 0;
 *   virtual int send(void* src, void *opt) = 0;
 *   virtual void on_send(int status, void *opt) = 0;
 *   void *on_send_param;
 * }
 *
 * Read below for serialize(), send() and on_send() semantics
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The service sending function that will be doing actual sending.
 *
 * NB: There is no send(dst, src, src_sz) function provided with this API to discourage
 * unnecessary memcpy()s. The function must be using in async mode - the status will be
 * given via on_send() callback.
 * \arg me - the service
 * \arg src - the app-specific data, which has to serialized by the app
 * \arg on_send_opt - an opaque parameter which will be supplied to on_send() callback
 * \return nothing - the app must rely on the callback for status
 */
typedef void (*mconn_service_send_fn)(mconn_service_t* me, void* src, void* on_send_opt);

// all services should be defined statically and shared as extern * pointers
// to user applications.
// The app is allowed to register own on_send(), on_send_param and serialize()
struct mconn_service_s {
    const uint8_t app_id;
    const uint8_t msg_type;
    mconn_service_serialize_payload_fn serialize;
    mconn_service_send_fn const send;
    mconn_on_transmit_cb on_send;
};

/**
 * Wether svc->send() is allowed. To be set by server app.
 */
extern int mconn_service_ready_to_send;

#ifdef __cplusplus
}
#endif
