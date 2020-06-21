/* See LICENSE file for copyright and license details. */
#include "common.h"

void
libaxl_context_free(LIBAXL_CONTEXT *ctx)
{
	if (ctx && !--ctx->refcount) {
		free(ctx->out_buf);
		free(ctx->in_buf);
		free(ctx->aux_buf);
		free(ctx);
	}
}
