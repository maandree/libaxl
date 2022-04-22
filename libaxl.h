/* See LICENSE file for copyright and license details. */
#ifndef LIBAXL_H
#define LIBAXL_H 2

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__)
# define _LIBAXL_GCC_ONLY(...) __VA_ARGS__
#else
# define _LIBAXL_GCC_ONLY(...)
#endif

/**
 * Opaque structure for connection to the X display server
 */
typedef struct libaxl_connection LIBAXL_CONNECTION; /* TODO man(makefile) */

/**
 * Opaque structure that wraps LIBAXL_CONNECTION with
 * private data for the thread, all threads running at
 * the same time shall access the display server
 * via a unique LIBAXL_CONTEXT
 */
typedef struct libaxl_context LIBAXL_CONTEXT; /* TODO man(makefile) */

#include "libaxl/types.h"
#include "libaxl/consts.h"
#include "libaxl/atoms.h"
#include "libaxl/events.h"
#include "libaxl/errors.h"
#include "libaxl/requests.h"
#include "libaxl/replies.h"
#include "libaxl/display-info.h"
#include "libaxl/advanced.h"
#include "libaxl/low-level.h"

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
#define LIBAXL_ERROR_INVALID_HANDSHAKE_RESPONSE                       -12
#define LIBAXL_ERROR_OUT_OF_RESOURCE_IDS                              -13
#define LIBAXL_ERROR_PROTOCOL_NOT_SUPPORTED                           -14
#define LIBAXL_ERROR_USER_DOES_NOT_EXIST                              -15
#define LIBAXL_ERROR_USER_DOES_NOT_HAVE_A_HOME                        -16

union libaxl_input { /* TODO doc, man(makefile) (also LIBAXL_SYNTHETIC_EVENT_BIT(~makefile)) */
	uint8_t            type;
	union libaxl_error error; /* if .type = LIBAXL_ERROR */
	union libaxl_reply reply; /* if .type = LIBAXL_REPLY */
	union libaxl_event event; /* otherwise (.type = event type) */
};

/**
 * Bit that is set in `.type` of `union libaxl_input` if the
 * event a synthetic event.
 */
#define LIBAXL_SYNTHETIC_EVENT_BIT 0x80U

/**
 * Connect to a display server and preform the connection handshake
 * 
 * @param   display  The display name string, $DISPLAY will be used if `NULL` or empty; see the
 *                   documentation for the libaxl_parse_display() for more details
 * @param   reasonp  Output parameter for the reason the handshake or authorisation failed;
 *                   The contents of the reason string are specific to the used authorisation
 *                   protocol. Will be set to `NULL` if not applicable.
 * @return           the connection object, will be set to `NULL` on error
 */
_LIBAXL_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__)))
LIBAXL_CONNECTION *libaxl_connect(const char *restrict, char **restrict); /* TODO man(makefile) */

/**
 * Deallocation and close a connection
 * 
 * @param   conn  The connection to the display server
 * @return        0 on success, -1 of there was an asynchronous error
 */
int libaxl_close(LIBAXL_CONNECTION *);

/**
 * Get the file description used for a connection to
 * the X display server
 * 
 * @param   conn  The connection to the display server
 * @return        The number of the file descriptor that holds
 *                the connection to the display server
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
int libaxl_fileno(LIBAXL_CONNECTION *);

/**
 * Get information about a connection and the display
 * and display server it is connected to
 * 
 * This information is sent to the client during the
 * connection handshake, and is never updated hence
 * 
 * @param   conn     The connection to the display server
 * @param   version  Should be `LIBAXL_DISPLAY_INFO_VERSION`; used to
 *                   identify if old fields that have been replaces
 *                   must allocated and filled in with information
 *                   from the new fields that the application does
 '                   not know about
 * @return           Information about the display, the display
 *                   server, and the connection; `NULL` on error
 * 
 * On failure, no error is returned, but the error
 * is always LIBAXL_ERROR_SYSTEM
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__, __const__)))
const struct libaxl_display_info *libaxl_info(LIBAXL_CONNECTION *, int); /* TODO man(makefile) */

/**
 * Get the next element in a `struct libaxl_depth *`
 * 
 * Usage example for iterating of all elements in
 * `screen->allowed_depths` where `screen` is a
 * `struct libaxl_screen *`:
 * 
 *         struct libaxl_depth *depth;
 *         size_t i = 0;
 *         for (depth = screen->allowed_depths; i < screen->number_of_allowed_depths; depth = libaxl_next_depth(depth)) {
 *             ... do something with `depth` or `break` if `i` is of a desired value (index) ...
 *         }
 * 
 * Note, the function does not check if another
 * element exists
 * 
 * @param   depth  The element before the element to return
 * @return         The element after `depth`
 */
_LIBAXL_GCC_ONLY(__attribute__((__warn_unused_result__, __pure__, __nonnull__, __returns_nonnull__)))
inline const struct libaxl_depth *
libaxl_next_depth(const struct libaxl_depth *depth) /* TODO man(makefile) */
{
	return (const struct libaxl_depth *)(uintptr_t)&depth->visuals[depth->number_of_visuals];
}

/**
 * Get the next element in a `struct libaxl_screen *`
 * 
 * Usage example for iterating of all elements in `info->screens`
 * where `info` is a `struct libaxl_display_info *`:
 * 
 *         struct libaxl_screen *screen;
 *         size_t i = 0;
 *         for (screen = info->screens; i < info->nscreens; screen = libaxl_next_screen(screen)) {
 *             ... do something with `screen` or `break` if `i` is of a desired value (index) ...
 *         }
 * 
 * Note, the function does not check if another
 * element exists
 * 
 * @param   screen  The element before the element to return
 * @return          The element after `screen`
 */
_LIBAXL_GCC_ONLY(__attribute__((__warn_unused_result__, __pure__, __nonnull__, __returns_nonnull__)))
inline const struct libaxl_screen *
libaxl_next_screen(const struct libaxl_screen *screen) /* TODO man(makefile) */
{
	uint8_t n = screen->number_of_allowed_depths;
	const struct libaxl_depth *depth = screen->allowed_depths;
	while (n--)
		depth = libaxl_next_depth(depth);
	return (const struct libaxl_screen *)(uintptr_t)depth;
}

/**
 * Create context, for a thread, to use when accessing
 * the display server
 * 
 * @param   conn  The connection to the display server
 * @return        The context, `NULL` on failure (can only be out of memory)
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __malloc__, __warn_unused_result__)))
LIBAXL_CONTEXT *libaxl_context_create(LIBAXL_CONNECTION *);

/**
 * Deallocate a context
 * 
 * @param  ctx  The context to deallocate
 */
void libaxl_context_free(LIBAXL_CONTEXT *);

/**
 * Generate a resource ID
 * 
 * The generated resource ID can be deallocated
 * with the libaxl_deallocate_id() function
 * 
 * @param   ctx  The thread's context for the connection
 * @return       The generated resource ID, 0 on failure
 * 
 * On failure, no error is returned, but the error
 * is always LIBAXL_ERROR_OUT_OF_RESOURCE_IDS
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
libaxl_id_t libaxl_generate_id(LIBAXL_CONTEXT *);

/**
 * Deallocate a resource ID so that it can be reused later
 * 
 * @param   ctx  The thread's context for the connection
 * @param   id   The generated resource ID to deallocate
 * @return       0 on success, a negative libaxl error code on failure
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__)))
int libaxl_deallocate_id(LIBAXL_CONTEXT *, libaxl_id_t);

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
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__(1))))
int libaxl_send_request(LIBAXL_CONTEXT *restrict, union libaxl_request_const_ptr, int, uint16_t *restrict); /* TODO man(makefile) */

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
int libaxl_flush(LIBAXL_CONNECTION *restrict, int); /* TODO man(makefile) */

/**
 * Receive the next pending message from the display server
 * 
 * Be aware: order of replies and events is not guaranteed,
 * and events caused by a request are sent before replies
 * and errors, however when multiple events are generated,
 * by some action, they are send in an uninterrupted sequence
 * (no other event, error, or reply is send between those event).
 * This means that it is important to check the returned
 * sequence number.
 * 
 * @param   ctx    The thread's context for the connection to the display server
 * @param   msgp   Output parameter for the received message; the message will
 *                 be vaild until the next time this function is called with the
 *                 same `ctx` parameter or until the libaxl_context_free() function
 *                 is called with the same `ctx` paramter (whichever comes first)
 * @param   flags  Flags to use for the 4th parameter when calling recv(3)
 * @return         0 on success, a negative libaxl error code on failure
 * 
 * Behaviour is unspecified if SO_PEEK_OFF is active on the
 * connection to the display server or if the MSG_PEEK flag
 * is used
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__)))
int libaxl_receive(LIBAXL_CONTEXT *restrict, union libaxl_input *restrict, int); /* TODO man(makefile) */

#undef LIBAXL_H
#define LIBAXL_H 1
#endif
