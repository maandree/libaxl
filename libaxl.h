/* See LICENSE file for copyright and license details. */
#ifndef LIBAXL_H
#define LIBAXL_H

#include <stddef.h>
#include <stdint.h>

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
#include "libaxl-display-info.h"

/**
 * The major version number of the highest version of X protocol
 * of the library supports (the lowest version is 11.0). If you
 * are using dynamic linking, you make also want to use the
 * libaxl_protocol_major() function.
 */
#define LIBAXL_PROTOCOL_MAJOR 11

/**
 * The minor version number of the highest version of X protocol
 * of the library supports (the lowest version is 11.0). If you
 * are using dynamic linking, you make also want to use the
 * libaxl_protocol_minor() function.
 */
#define LIBAXL_PROTOCOL_MINOR 0

/**
 * The version number of the highest version of X protocol of
 * the library supports, as one integer where the major number
 * is multiped by 100000, (the lowest version is 11.0, which is
 * encoded as 1100000). If you are using dynamic linking, you
 * make also want to use the libaxl_protocol_version() function.
 */
#define LIBAXL_PROTOCOL_VERSION ((LIBAXL_PROTOCOL_MAJOR) * 100000 + (LIBAXL_PROTOCOL_MINOR))

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

#define LIBAXL_HANDSHAKE_FAILED       0
#define LIBAXL_HANDSHAKE_SUCCESS      1
#define LIBAXL_HANDSHAKE_AUTHENTICATE 2

/*
 * The largest possible return of the libaxl_get_decnet_object()
 * function, plus 1 for the terminal NUL byte
 */
#define LIBAXL_DECNET_OBJECT_MAX (5 + 3 * sizeof(int) - sizeof(int) / 2)

union libaxl_input { /* TODO doc, man */
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
 * Returns the major version number of the highest version of
 * X protocol of the library supports (the lowest version is
 * 11.0). If you are using static linking, you make also want
 * to use the LIBAXL_PROTOCOL_MAJOR constant.
 * 
 * @return  The major version number of highest support version of the protocol
 */
int libaxl_protocol_version_major(void);

/**
 * Returns the minor version number of the highest version of
 * X protocol of the library supports (the lowest version is
 * 11.0). If you are using static linking, you make also want
 * to use the LIBAXL_PROTOCOL_MINOR constant.
 * 
 * @return  The minor version number of highest support version of the protocol
 */
int libaxl_protocol_version_minor(void);

/**
 * Returns the minor version number of the highest version of
 * X protocol of the library supports (the lowest version is 11.0,
 * which is encoded as 1100000). If you are using static linking,
 * you make also want to use the LIBAXL_PROTOCOL_VERSION constant.
 * 
 * @return  The version number of highest support version of the protocol,
 *          encoded as a sum of the major number multipled by 100000 (1e5)
 *          and the minor number, e.g. 1100000 for 11.0 (X11)
 */
int libaxl_protocol_version(void);

/**
 * Get the file description used for a connection to
 * the X display server
 * 
 * @param   conn  The connection to the display server
 * @return        The number of the file descriptor that holds
 *                the connection to the display server
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
int libaxl_fileno(LIBAXL_CONNECTION *); /* TODO man */

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
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
const struct libaxl_display_info *libaxl_info(LIBAXL_CONNECTION *, int); /* TODO man */

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
 * @param   depth  The element before the element to return
 * @return         The element after `depth`
 */
inline const struct libaxl_depth *
libaxl_next_depth(const struct libaxl_depth *depth) /* TODO man */
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
 * @param   screen  The element before the element to return
 * @return          The element after `screen`
 */
inline const struct libaxl_screen *
libaxl_next_screen(const struct libaxl_screen *screen) /* TODO man */
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
 * with the libaxl_deallocate_id() function
 * 
 * @param   ctx  The thread's context for the connection
 * @return       The generated resource ID, 0 on failure
 * 
 * On failure, no error is returned, but the error
 * is always LIBAXL_ERROR_OUT_OF_RESOURCE_IDS
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
libaxl_id_t libaxl_generate_id(LIBAXL_CONTEXT *); /* TODO man */

/**
 * Deallocate a resource ID so that it can be reused later
 * 
 * @param   ctx  The thread's context for the connection
 * @param   id   The generated resource ID to deallocate
 * @return       0 on success, a negative libaxl error code on failure
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__)))
int libaxl_deallocate_id(LIBAXL_CONTEXT *, libaxl_id_t); /* TODO man, implement */

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
 * @param   name       The display name string, $DISPLAY will be used if NULL or empty
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
 * Get the TCP port that is used for a display
 * 
 * @param   display  The display's number, the function will assume that it is a valid number
 * @return           The TCP port used for the display
 */
_LIBAXL_GCC_ONLY(__attribute__((__warn_unused_result__, __const__)))
inline uint16_t libaxl_get_tcp_port(int display) /* TODO man */
{
	return (uint16_t)(display + 6000);
}

/**
 * Get the DECnet object name that is used for a display
 * 
 * @param   buf      Buffer that the object name shall be written to, it is recommended
 *                   that is size, if static, is LIBAXL_DECNET_OBJECT_MAX (which is
 *                   always sufficient), otherwise it should be at least the return value
 *                   of this function (for the same last argument but with NULL and 0
 *                   as the first two arguments) plus 1
 * @param   size     The size of the buffer in the `buf` argument
 * @param   display  The display's number
 * @return           The length of the object name, will not exceed LIBAXL_DECNET_OBJECT_MAX
 *                   less 1; an additional uncounted NUL byte will be written to the buffer
 *                   if it is large enough; or -1 on failure (specifically snprintf(3), which
 *                   the function calls, by fail with EOVERFLOW if the `size` argument is
 *                   greater than {INT_MAX})
 */
int libaxl_get_decnet_object(char *, size_t, int); /* TODO man */

/**
 * This function is to be called once and only once, excluding any
 * failure that does not set `errno` to EINPROGRESS and excluding
 * any call for which the display server respond that the handshake
 * failed or requires authentication, immediately after connecting
 * to the socket for the display
 * 
 * The libaxl_receive_handshake() shall be called immediately after
 * calling this function
 * 
 * @param   ctx            The thread's context for the connection to the display to send the handshake over
 * @param   auth_name      The protocol name of the authorisation the client expects the server to use;
 *                         valid authorisation mechanisms are not part of the core X protocol
 * @param   auth_name_len  The length of `auth_name`, 0 if `auth_name` is NULL
 * @param   auth_data      The authorisation data, which is specific to the choosen authorisation mechanism
 * @param   auth_data_len  The length of `auth_data`, 0 if `auth_data` is NULL
 * @param   flags          Flags to use for the 4th parameter when calling send(3)
 * @return                 0 on success, a negative libaxl error code on failure
 * 
 * If the function returns LIBAXL_ERROR_SYSTEM and sets `errno`
 * to EINPROGRESS, the message has been saved (possibly partially
 * sent) and pending to be sent by calling libaxl_flush().
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__(1))))
int libaxl_send_handshake(LIBAXL_CONTEXT *restrict, const char *, size_t, const char *, size_t, int); /* TODO man */

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
 * Receive the server's part of the handshake, this function
 * shall be called once immediately after each successful call
 * to the libaxl_send_handshake() function or successful call
 * to the libaxl_flush() function due to EINPROGRESS failure
 * of call to the libaxl_send_handshake() function
 * 
 * @param   ctx      The thread's context for the connection to the display server
 * @param   majorp   Output parameter for the major version number for a version
 *                   of the X protocol that the display server supports, which is
 *                   not necessarily the version that the library uses. Will only
 *                   be set if the function returns LIBAXL_HANDSHAKE_FAILED or
 *                   LIBAXL_HANDSHAKE_SUCCESS.
 * @param   minorp   Output parameter for the minor version number for a version
 *                   of the X protocol that the display server supports, which is
 *                   not necessarily the version that the library uses. Will only
 *                   be set if the function returns LIBAXL_HANDSHAKE_FAILED or
 *                   LIBAXL_HANDSHAKE_SUCCESS.
 * @param   reasonp  Output parameter for the reason the handshake or authorisation
 *                   failed. Will be set to NULL unless the function returns
 *                   LIBAXL_HANDSHAKE_FAILED or LIBAXL_HANDSHAKE_AUTHENTICATE.
 *                   Remember to free after successful completion (non-negative return)
 * @param   flags    Flags to use for the 4th parameter when calling recv(3)
 * @return           0 on success, a negative libaxl error code on failure
 * 
 * Behaviour is unspecified if SO_PEEK_OFF is active on the
 * connection to the display server or if the MSG_PEEK flag
 * is used
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__(1))))
int libaxl_receive_handshake(LIBAXL_CONTEXT *restrict, int *restrict, int *restrict, char **restrict, int); /* TODO man */

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
int libaxl_receive(LIBAXL_CONTEXT *restrict, union libaxl_input *restrict, int); /* TODO man */

#endif
