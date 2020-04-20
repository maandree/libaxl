/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_flush(LIBAXL_CONNECTION *restrict conn, int flags)
{
	LIBAXL_CONTEXT *ctx;
	ssize_t r;

	WLOCK_CONNECTION_SEND(conn);

	while ((ctx = conn->pending_out)) {
		while (ctx->out_progress < ctx->out_length) {
			r = liberror_send(conn->fd, &ctx->out_buf[ctx->out_progress],
			                  ctx->out_length - ctx->out_progress, flags, "<display server>");
			if (r < 0) {
				WUNLOCK_CONNECTION_SEND(conn);
				return LIBAXL_ERROR_SYSTEM;
			}
			ctx->out_progress += (size_t)r;
		}

		conn->pending_out = ctx->next_pending_out;
		libaxl_context_free(ctx);
	}

	WUNLOCK_CONNECTION_SEND(conn);

	return 0;
}
