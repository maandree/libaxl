/* See LICENSE file for copyright and license details. */
#ifndef LIBAXL_H
#define LIBAXL_H

#if defined(__GNUC__)
# define _LIBAXL_GCC_ONLY(...) __VA_ARGS__
#else
# define _LIBAXL_GCC_ONLY(...)
#endif

#include "libaxl-types.h"
#include "libaxl-consts.h"
#include "libaxl-atoms.h"
#include "libaxl-events.h"
#include "libaxl-errors.h"
#include "libaxl-requests.h"
#include "libaxl-replies.h"

/* libaxl error codes */
#define LIBAXL_ERROR_SYSTEM                                           -1 /* use `errno` */
#define LIBAXL_ERROR_NO_DISPLAY_SERVER_SPECIFIED                      -2
#define LIBAXL_ERROR_INVALID_DISPLAY_NAME_NO_DISPLAY_INDEX            -3
#define LIBAXL_ERROR_INVALID_DISPLAY_NAME_DISPLAY_INDEX_OUT_OF_DOMAIN -4
#define LIBAXL_ERROR_INVALID_DISPLAY_NAME_INVALID_SCREEN_INDEX        -5
#define LIBAXL_ERROR_INVALID_DISPLAY_NAME_SCREEN_INDEX_OUT_OF_DOMAIN  -6
#define LIBAXL_ERROR_INVALID_REQUEST_OPCODE                           -7
#define LIBAXL_ERROR_INVALID_FORMAT_NUMBER                            -8
#define LIBAXL_ERROR_MALFORMATTED_REQUEST                             -9
#define LIBAXL_ERROR_CONNECTION_CLOSED                                -10
#define LIBAXL_ERROR_INVALID_REPLY_OPCODE                             -11

union libaxl_input { /* TODO man */
	uint8_t            type;
	union libaxl_error error; /* if .type = LIBAXL_ERROR */
	union libaxl_reply reply; /* if .type = LIBAXL_REPLY */
	union libaxl_event event; /* otherwise (.type = event type) */
};

/**
 * Opaque structure for connection to the X display server
 */
typedef struct libaxl_connection LIBAXL_CONNECTION;

/**
 * Opaque structure that wraps LIBAXL_CONNECTION with
 * private data for the thread, all threads running at
 * the same time shall access the display server
 * via a unique LIBAXL_CONTEXT
 */
typedef struct libaxl_context LIBAXL_CONTEXT;

/**
 * Create context, for a thread, to use when accessing
 * the display server
 * 
 * @param   conn  The connection to the display server
 * @return        The context, NULL on failure (can only be out of memory)
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __malloc__, __warn_unused_result__)))
LIBAXL_CONTEXT *libaxl_context_create(LIBAXL_CONNECTION *); /* TODO man */

/**
 * Deallocate a context
 * 
 * @param  ctx  The context to deallocate
 */
void libaxl_context_free(LIBAXL_CONTEXT *); /* TODO man */

/**
 * Generate a resource ID
 * 
 * The generated resource ID can be deallocated
 * with the `libaxl_deallocate_id` function
 * 
 * @param   ctx  The thread's context for the connection
 * @return       The generated resource ID, 0 on failure
 */
libaxl_id_t libaxl_generate_id(LIBAXL_CONTEXT *); /* TODO man, implement */

/**
 * Deallocate a resource ID so that it can be reused later
 * 
 * @param  ctx  The thread's context for the connection
 * @param  id   The generated resource ID to deallocate
 */
void libaxl_deallocate_id(LIBAXL_CONTEXT *, libaxl_id_t); /* TODO man, implement */

/**
 * Parse a display name string
 * 
 * The format for the display name string shall be either
 * 
 *     [<protocol>/][<host>]:<display>[.<screen>]
 * 
 * or for the "unix" protocol
 * 
 *     <path>[.<screen>]
 * 
 * @param   name       The display name string, $DISPLAY will be used if `NULL` or empty
 * @param   hostp      Output parameter for the host of or (if the protocol is "unix") path
 *                     to the display, remember to free after successful completion
 * @param   protocolp  Output parameter for the network protocol used to access the display,
 *                     remember to free after successful completion
 * @param   displayp   Output parameter for the display's index (0 if the protocol is "unix")
 * @param   screenp    Output parameter for the screen's index
 * @return             0 on success, a negative libaxl error code on failure
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__(2, 3, 4, 5))))
int libaxl_parse_display(const char *, char **, char **, int *, int *); /* TODO man */

/**
 * Send a request to the display server
 * 
 * May deadlock if called from an asynchronously called signal handler
 * 
 * @param   ctx      The thread's context for the connection to the display to send the request over
 * @param   request  The request to send, the function will not edit the content
 * @param   flags    Flags to use for the 4th parameter when calling send(3)
 * @param   seqnump  Output parameter for the request's sequence number
 * @return           0 on success, a negative libaxl error code on failure
 * 
 * If the function returns LIBAXL_ERROR_SYSTEM and sets `errno`
 * to EINPROGRESS, the message has been saved (possibly partially
 * sent) and pending to be sent by calling libaxl_flush(). In this
 * case (and on success), `*seqnump` will be set.
 * 
 * If the function returns LIBAXL_ERROR_SYSTEM and sets `errno`
 * to EALREADY, libaxl_flush() must first be called, either because
 * the previous call to this function returned LIBAXL_ERROR_SYSTEM
 * and set `errno` to EINPROGRESS, or such happened in another
 * thread.
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__)))
int libaxl_send_request(LIBAXL_CONTEXT *restrict, union libaxl_request_const_ptr, int, uint16_t *restrict); /* TODO man */

/**
 * Send any pending messages to the display server
 * 
 * @param   conn   The connection to the display server to flush
 * @param   flags  Flags to use for the 4th parameter when calling send(3)
 * @return         0 on success, a negative libaxl error code on failure
 * 
 * If the function returns LIBAXL_ERROR_SYSTEM and sets `errno`
 * to EINPROGRESS, call the function again. Note well, the
 * EINPROGRESS error is caused by some other error, which could
 * be EAGAIN (otherwise its probably EINTR). On success, there
 * is nothing more to flush.
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__)))
int libaxl_flush(LIBAXL_CONNECTION *restrict, int); /* TODO man */

/**
 * Receive the next pending message from the display server
 * 
 * @param  ctx    The thread's context for the connection to the display server
 * @param  msgp   Output parameter for the received message; the message will
 *                be vaild until the next time this function is called with the
 *                same `ctx` parameter or until the libaxl_context_free() function
 *                is called with the same `ctx` paramter (whichever comes first)
 * @param  flags  Flags to use for the 4th parameter when calling recv(3)
 * 
 * Behaviour is unspecified if SO_PEEK_OFF is active on the
 * connection to the display server or if the MSG_PEEK flag
 * is used
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__)))
int libaxl_receive(LIBAXL_CONTEXT *restrict, union libaxl_input *restrict, int); /* TODO man */

#endif
