/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_close(LIBAXL_CONNECTION *conn)
{
	return liberror_close(libaxl_detach(conn));
}
