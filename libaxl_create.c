/* See LICENSE file for copyright and license details. */
#include "common.h"

LIBAXL_CONNECTION *
libaxl_create(int fd)
{
	LIBAXL_CONNECTION *conn;
	conn = liberror_calloc(1, sizeof(*conn));
	if (conn) {
		conn->fd = fd;
		atomic_init(&conn->xid_last, 0);
		INIT_LIBAXL_CONNECTION_RWLOCK(conn);
	}
	return conn;
}
