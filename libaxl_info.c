/* See LICENSE file for copyright and license details. */
#include "common.h"

const struct libaxl_display_info *
libaxl_info(LIBAXL_CONNECTION *conn, int version)
{
	(void) version;
	return &conn->info;
}
