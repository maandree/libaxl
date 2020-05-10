/* See LICENSE file for copyright and license details. */
#include "common.h"

void
libaxl_attach(LIBAXL_CONNECTION *conn, int fd)
{
	conn->fd = fd;
}
