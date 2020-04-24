/* See LICENSE file for copyright and license details. */
#include "common.h"

libaxl_id_t
libaxl_generate_id(LIBAXL_CONTEXT *ctx)
{
	LIBAXL_CONNECTION *conn = ctx->conn;
	uint32_t id;

	id = atomic_fetch_add(&conn->xid_last, 1);
	if (id <= conn->xid_max)
		return (id << conn->xid_shift) | conn->xid_base;

	atomic_fetch_sub(&conn->xid_last, 1);

	liberror_save_backtrace(NULL);
	liberror_set_error("Request has been buffered and is ready to be sent",
	                   "libaxl_generate_id", "libaxl", LIBAXL_ERROR_OUT_OF_RESOURCE_IDS);
	return 0;
}
