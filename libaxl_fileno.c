/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_fileno(LIBAXL_CONNECTION *conn)
{
	return conn->fd;
}
