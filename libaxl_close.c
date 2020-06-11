/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_close(LIBAXL_CONNECTION *conn)
{
	if (!conn)
		return 0;
	return liberror_close(libaxl_detach(conn));
}
