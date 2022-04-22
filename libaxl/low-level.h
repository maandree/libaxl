/* See LICENSE file for copyright and license details. */

#if !defined(LIBAXL_H) || (LIBAXL_H < 2)
# error Do not include <libaxl/low-level.h> directly, include <libaxl.h> instead.
#endif

#define LIBAXL_HANDSHAKE_FAILED       0 /* Handshake failed  */
#define LIBAXL_HANDSHAKE_SUCCESS      1 /* Handshake succeeded */
#define LIBAXL_HANDSHAKE_AUTHENTICATE 2 /* Further authnetication is required */

/*
 * The largest possible return of the libaxl_get_decnet_object()
 * function, plus 1 for the terminal NUL byte
 */
#define LIBAXL_DECNET_OBJECT_MAX (5 + 3 * sizeof(int) - sizeof(int) / 2)

/**
 * Create a connection object for a socket
 * 
 * @param   fd  The file descriptor for the socket of the
 *              connection (does not have to be connected yet)
 * @return      The connection object, `NULL` on error
 * 
 * On failure, no error is returned, but the error
 * is always LIBAXL_ERROR_SYSTEM
 */
_LIBAXL_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__)))
LIBAXL_CONNECTION *libaxl_create(int);

/**
 * Connect to a display server, but do not initiate the handshake
 *
 * The libaxl_send_handshake() function can be used to initiate
 * the handshake
 * 
 * @param   host      The host of or (if the protocol is "unix") path to the display
 * @param   protocol  The network protocol used to access the display
 * @param   display   The display's index (0 if the protocol is "unix")
 * @param   screen    The screen's index (-1 of not specified)
 * @return            The connection object, `NULL` on error
 * 
 * The parameters host, protocol, display, and screen can be
 * parsed from e.g. the DISPLAY environment variable using
 * the libaxl_parse_display() function
 * 
 * On failure, no error is returned, but the error
 * is always LIBAXL_ERROR_SYSTEM
 */
_LIBAXL_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__)))
LIBAXL_CONNECTION *libaxl_connect_without_handshake(const char *host, const char *protocol, int display, int screen); /* TODO man(makefile; ref libaxl_parse_display, libaxl_send_handshake, libaxl_connect) */

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
 * @param   screenp    Output parameter for the screen's index (-1 of not specified)
 * @return             0 on success, a negative libaxl error code on failure
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__(2, 3, 4, 5))))
int libaxl_parse_display(const char *, char **, char **, int *, int *);

/**
 * Get the TCP port that is used for a display
 * 
 * @param   display  The display's number, the function will assume that it is a valid number
 * @return           The TCP port used for the display
 */
_LIBAXL_GCC_ONLY(__attribute__((__warn_unused_result__, __const__)))
inline uint16_t libaxl_get_tcp_port(int display)
{
	return (uint16_t)(display + 6000);
}

/**
 * Get the DECnet object name that is used for a display
 * 
 * @param   buf      Buffer that the object name shall be written to, it is recommended
 *                   that its size, if static, is LIBAXL_DECNET_OBJECT_MAX (which is
 *                   always sufficient), otherwise it should be at least the return value
 *                   of this function (for the same last argument but with `NULL` and 0
 *                   as the first two arguments) plus 1
 * @param   size     The size of the buffer in the `buf` argument
 * @param   display  The display's number
 * @return           The length of the object name, will not exceed LIBAXL_DECNET_OBJECT_MAX
 *                   less 1; an additional uncounted NUL byte will be written to the buffer
 *                   if it is large enough; or -1 on failure (specifically snprintf(3), which
 *                   the function calls, will fail with EOVERFLOW if the `size` argument is
 *                   greater than {INT_MAX})
 */
int libaxl_get_decnet_object(char *, size_t, int);

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
 * @param   auth_name_len  The length of `auth_name`, 0 if `auth_name` is `NULL`
 * @param   auth_data      The authorisation data, which is specific to the choosen authorisation mechanism
 * @param   auth_data_len  The length of `auth_data`, 0 if `auth_data` is `NULL`
 * @param   flags          Flags to use for the 4th parameter when calling send(3)
 * @return                 0 on success, a negative libaxl error code on failure
 * 
 * If the function returns LIBAXL_ERROR_SYSTEM and sets `errno`
 * to EINPROGRESS, the message has been saved (possibly partially
 * sent) and pending to be sent by calling libaxl_flush().
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__(1))))
int libaxl_send_handshake(LIBAXL_CONTEXT *restrict, const char *, size_t, const char *, size_t, int);

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
 *                   failed; the contents are specific to the authorisation protocol
 *                   in use Will be set to `NULL` unless the function returns
 *                   LIBAXL_HANDSHAKE_FAILED or LIBAXL_HANDSHAKE_AUTHENTICATE.
 *                   Remember to free after successful completion (non-negative return)
 * @param   flags    Flags to use for the 4th parameter when calling recv(3)
 * @return           LIBAXL_HANDSHAKE_SUCCESS (NB! this value is not 0) on
 *                   success, LIBAXL_HANDSHAKE_FAILED on handshake failure,
 *                   LIBAXL_HANDSHAKE_AUTHENTICATE if further authentication is
 *                   required, or a negative libaxl error code on failure
 * 
 * Behaviour is unspecified if SO_PEEK_OFF is active on the
 * connection to the display server or if the MSG_PEEK flag
 * is used
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__(1))))
int libaxl_receive_handshake(LIBAXL_CONTEXT *restrict, int *restrict, int *restrict, char **restrict, int);
