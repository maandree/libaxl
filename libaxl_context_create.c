/* See LICENSE file for copyright and license details. */
#include "common.h"

LIBAXL_CONTEXT *
libaxl_context_create(LIBAXL_CONNECTION *conn)
{
	LIBAXL_CONTEXT *ctx;
	ctx = liberror_malloc(sizeof(*ctx));
	if (ctx) {
		ctx->conn         = conn;
		ctx->refcount     = 1;
		ctx->out_buf_size = 0;
		ctx->out_buf      = NULL;
		ctx->in_buf_size  = 0;
		ctx->in_buf       = NULL;
	}
	return ctx;
}
