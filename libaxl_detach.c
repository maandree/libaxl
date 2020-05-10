/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_detach(LIBAXL_CONNECTION *conn)
{
	int fd = conn->fd;
	LIBAXL_CONTEXT *ctx;
	while (conn->pending_out) {
		ctx = conn->pending_out;
		conn->pending_out = ctx->next_pending_out;
		libaxl_context_free(ctx);
	}
	free(conn->in_buf);
	free(conn->info_buf);
	free(conn);
	return fd;
}
