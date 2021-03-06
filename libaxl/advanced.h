/* See LICENSE file for copyright and license details. */

#if !defined(LIBAXL_H) || (LIBAXL_H < 2)
# error Do not include <libaxl/advanced.h> directly, include <libaxl.h> instead.
#endif

/**
 * The major version number of the highest version of X protocol
 * of the library supports (the lowest version is 11.0). If you
 * are using dynamic linking, you may also want to use the
 * `libaxl_protocol_version_major` variable.
 */
#define LIBAXL_PROTOCOL_VERSION_MAJOR 11

/**
 * The minor version number of the highest version of X protocol
 * of the library supports (the lowest version is 11.0). If you
 * are using dynamic linking, you may also want to use the
 * `libaxl_protocol_version_minor` variable.
 */
#define LIBAXL_PROTOCOL_VERSION_MINOR 0

/**
 * The version number of the highest version of X protocol of
 * the library supports, as one integer where the major number
 * is multiped by 1000, (the lowest version is 11.0, which is
 * encoded as 11000). If you are using dynamic linking, you
 * may also want to use the `libaxl_protocol_version` variable.
 */
#define LIBAXL_PROTOCOL_VERSION ((LIBAXL_PROTOCOL_VERSION_MAJOR) * 1000 + (LIBAXL_PROTOCOL_VERSION_MINOR))

/**
 * The major version number of the highest version of
 * X protocol of the library supports (the lowest version is
 * 11.0). If you are using static linking, you may also want
 * to use the LIBAXL_PROTOCOL_VERSION_MAJOR constant.
 */
extern const int libaxl_protocol_version_major;

/**
 * The minor version number of the highest version of
 * X protocol of the library supports (the lowest version is
 * 11.0). If you are using static linking, you may also want
 * to use the LIBAXL_PROTOCOL_VERSION_MINOR constant.
 */
extern const int libaxl_protocol_version_minor;

/**
 * Returns the version number, encoded as the sum of the major
 * number multipled by 1000 and the minor number (e.g. 11000
 * for 11.0 (X11)), of the highest version of X protocol of
 * the library supports (the lowest version is 11.0, which is
 * encoded as 11000). If you are using static linking, you
 * may also want to use the LIBAXL_PROTOCOL_VERSION constant.
 */
extern const int libaxl_protocol_version;

/**
 * Deallocations a connection object without
 * closing the file descriptor, which instead
 * is returned
 * 
 * @param   conn  The connection to the display server
 * @return        The file descriptor of the connection
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
int libaxl_detach(LIBAXL_CONNECTION *);

/**
 * Change the file descriptor of a connection
 * 
 * @param  conn  The connection to the display server
 * @param  fd    The new file descriptor
 */
_LIBAXL_GCC_ONLY(__attribute__((__nonnull__)))
void libaxl_attach(LIBAXL_CONNECTION *, int);
