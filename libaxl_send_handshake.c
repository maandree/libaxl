/* See LICENSE file for copyright and license details. */
#include "common.h"

static int
send_all(int fd, void *restrict data, size_t n, int flags, size_t *restrict progressp)
{
	char *bs = data;
	ssize_t r;

	while (n) {
		r = liberror_send(fd, bs, n, flags, "<display server>");
		if (r < 0)
			return -1;
		bs += r, n -= (size_t)r;
		*progressp += (size_t)r;
	}

	return 0;
}

int
libaxl_send_handshake(LIBAXL_CONTEXT *restrict ctx, const char *auth_name, size_t auth_name_len,
                      const char *auth_data, size_t auth_data_len, int flags)
{
	LIBAXL_CONNECTION *conn = ctx->conn;
	LIBAXL_CONTEXT *pending, **pendingp;
	size_t len, o = 0;
	char *buf;

	RLOCK_CONNECTION_SEND(conn);
	pending = conn->pending_out;
	conn->info.protocol_version_major = LIBAXL_PROTOCOL_MAJOR;
	conn->info.protocol_version_minor = LIBAXL_PROTOCOL_MINOR;
	conn->info.protocol_version       = LIBAXL_PROTOCOL_VERSION;
	conn->info.protocol_byte_order    = LIBAXL_MSB_FIRST; /* TODO Use LIBAXL_LSB_FIRST if preferable */
	RUNLOCK_CONNECTION_SEND(conn);
	if (pending) {
		liberror_save_backtrace(NULL);
		liberror_set_error(pending == ctx
		                   ? "Request from the previous call is pending to be flush"
		                   : "A request from another thread is pending to be flushed",
		                   "libaxl_send_handshake", "errno", EALREADY);
		errno = EALREADY;
		return LIBAXL_ERROR_SYSTEM;
	}

	if (auth_name_len > UINT16_MAX) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Authorisation protocol name is too long", "libaxl_send_handshake", "errno", EINVAL);
		errno = EINVAL;
		return LIBAXL_ERROR_SYSTEM;
	}

	if (auth_data_len > UINT16_MAX) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Authorisation data is too long", "libaxl_send_handshake", "errno", EINVAL);
		errno = EINVAL;
		return LIBAXL_ERROR_SYSTEM;
	}

	buf = ctx->out_buf;
	len = 12 + (auth_name_len + 3) / 4 * 4 + (auth_data_len + 3) / 4 * 4;
	if (len > ctx->out_buf_size) {
			buf = liberror_realloc(buf, len);
			if (!buf)
				return LIBAXL_ERROR_SYSTEM;
			ctx->out_buf = buf;
			ctx->out_buf_size = len;
	}

	buf[o++] = 'B'; /* TODO Use 'l' (LSB first) if preferable */
	buf[o++] = 0;
	*(uint16_t *)&buf[o] = htons(LIBAXL_PROTOCOL_MAJOR);
	o += 2;
	*(uint16_t *)&buf[o] = htons(LIBAXL_PROTOCOL_MINOR);
	o += 2;
	*(uint16_t *)&buf[o] = htons((uint16_t)auth_name_len);
	o += 2;
	*(uint16_t *)&buf[o] = htons((uint16_t)auth_data_len);
	o += 2;
	buf[o++] = 0;
	buf[o++] = 0;
	memcpy(&buf[o], auth_name, auth_name_len);
	for (o += auth_name_len; o % 4; o++)
		buf[o] = 0;
	memcpy(&buf[o], auth_data, auth_data_len);
	for (o += auth_data_len; o % 4; o++)
		buf[o] = 0;

	ctx->out_length = o;
	ctx->out_progress = 0;

	WLOCK_CONNECTION_SEND(conn);

	if (send_all(conn->fd, ctx->out_buf, ctx->out_length, flags, &ctx->out_progress)) {
		ctx->next_pending_out = NULL;
		pendingp = &conn->pending_out;
		while (*pendingp)
			pendingp = &(*pendingp)->next_pending_out;
		*pendingp = ctx;
		ctx->refcount += 1;

		WUNLOCK_CONNECTION_SEND(conn);

		liberror_save_backtrace(NULL);
		liberror_set_error("Handshake has been buffered and is ready to be sent",
		                   "libaxl_send_request", "errno", EINPROGRESS);
		errno = EINPROGRESS;
		return LIBAXL_ERROR_SYSTEM;
	}

	WUNLOCK_CONNECTION_SEND(conn);

	return 0;
}
