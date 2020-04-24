/* See LICENSE file for copyright and license details. */
#include "common.h"

struct response {
	uint8_t  status;
	uint8_t  length_of_reason; /* Only used in Failed, and not in Authenticate */
	uint16_t protocol_major_version; /* Not in Authenticate */
	uint16_t protocol_minor_version; /* Not in Authenticate */
	union {
		struct {
			uint16_t length_of_addition_data;
			char additional_data[];
		};
		struct {
			uint16_t __length_of_addition_data__1;
			char reason[];
		};
		struct {
			uint16_t __length_of_addition_data__2;
			uint32_t release_number;
			uint32_t resource_id_base;
			uint32_t resource_id_mask;
			uint32_t motion_buffer_size;
			uint16_t length_of_vendor;
			uint16_t maximum_request_length;
			uint8_t number_of_roots;
			uint8_t number_of_pixmap_formats;
			uint8_t image_byte_order;
			uint8_t bitmap_format_bit_order;
			uint8_t bitmap_format_scanline_unit;
			uint8_t bitmap_format_scanline_pad;
			uint8_t min_keycode;
			uint8_t max_keycode;
			uint32_t __unused;
			char vendor[];
		};
	};
};

int
libaxl_receive_handshake(LIBAXL_CONTEXT *restrict ctx, int *restrict majorp, int *restrict minorp, char **restrict reasonp, int flags)
{
	LIBAXL_CONNECTION *conn = ctx->conn;
	char *restrict inbuf, *new;
	size_t n, t, len, vendor_len, out_off, in_off;
	ssize_t r;
	int read_stage = 0, saved_errno;
	struct response *resp;
#ifdef MSG_TRUNC
	int flag_trunc;
#endif

#ifdef MSG_TRUNC
	flags ^= flag_trunc = flags & MSG_TRUNC;
#endif

	WLOCK_CONNECTION_RECV(conn);

	inbuf = conn->in_buf;
	n = offsetof(struct response, additional_data);

	if (conn->in_buf_size < n) {
		inbuf = liberror_realloc(inbuf, n);
		if (!inbuf) {
			WUNLOCK_CONNECTION_RECV(conn);
			return LIBAXL_ERROR_SYSTEM;
		}
		conn->in_buf = inbuf;
		conn->in_buf_size = n;
	}

continue_read:
	while (conn->in_progress < n) {
		r = recv(conn->fd, &inbuf[conn->in_progress], n - conn->in_progress, flags);
		if (r <= 0) {
			WUNLOCK_CONNECTION_RECV(conn);
			liberror_save_backtrace(NULL);
			if (!r) {
				liberror_set_error("The connection to the display server has been closed",
				                   "libaxl_receive_handshake", "libaxl", LIBAXL_ERROR_CONNECTION_CLOSED);
				return LIBAXL_ERROR_CONNECTION_CLOSED;
			}
			liberror_recv_failed(conn->fd, &inbuf[conn->in_progress], n - conn->in_progress, flags, "<display server>");
			return LIBAXL_ERROR_SYSTEM;
		}
		conn->in_progress += (size_t)r;
	}

	if (read_stage == 0) {
		n += (size_t)((struct response *)inbuf)->length_of_addition_data * 4;
		read_stage = 1;
		goto continue_read;
	}

	conn->in_progress = 0;

#ifdef MSG_TRUNC
	if (flag_trunc) {
		WUNLOCK_CONNECTION_RECV(conn);
		return 0;
	}
#endif

	t = conn->in_buf_size;
	conn->in_buf_size = ctx->in_buf_size;
	ctx->in_buf_size = t;

	conn->in_buf = ctx->in_buf;
	ctx->in_buf = inbuf;

	WUNLOCK_CONNECTION_RECV(conn);

	resp = (struct response *)inbuf;

	if (majorp)
		*majorp = (int)resp->protocol_major_version;
	if (minorp)
		*minorp = (int)resp->protocol_minor_version;
	if (reasonp)
		*reasonp = NULL;

	switch (resp->status) {
	case LIBAXL_HANDSHAKE_FAILED:
		len = (size_t)resp->length_of_reason;
		if (n < len + offsetof(struct response, reason))
			goto invalid;
		goto return_reason;

	case LIBAXL_HANDSHAKE_AUTHENTICATE:
		len = n - offsetof(struct response, reason);
	return_reason:
		if (reasonp) {
			*reasonp = liberror_malloc(len + 1);
			if (!*reasonp)
				return LIBAXL_ERROR_SYSTEM;
			memcpy(*reasonp, resp->reason, len);
			(*reasonp)[len] = '\0';
		}
		break;

	case LIBAXL_HANDSHAKE_SUCCESS:
		if (resp->resource_id_base & resp->resource_id_mask ||
		    (resp->resource_id_base | resp->resource_id_mask) >> 29)
			goto invalid;

		conn->xid_base = resp->resource_id_base;
		for (conn->xid_shift = 0; !(resp->resource_id_mask & 1); conn->xid_shift += 1)
			resp->resource_id_mask >>= 1;
		conn->xid_max = resp->resource_id_mask;
		conn->info.vendor_release              = resp->release_number;
		conn->info.min_keycode                 = resp->min_keycode;
		conn->info.max_keycode                 = resp->max_keycode;
		conn->info.image_byte_order            = resp->image_byte_order;
		conn->info.motion_buffer_size          = resp->motion_buffer_size;
		conn->info.maximum_request_length      = resp->maximum_request_length;
		conn->info.bitmap_format_bit_order     = resp->bitmap_format_bit_order;
		conn->info.bitmap_format_scanline_unit = resp->bitmap_format_scanline_unit;
		conn->info.bitmap_format_scanline_pad  = resp->bitmap_format_scanline_pad;

		/* These restricts are less restrictive than the protocol specifices,
		 * in case the they are modified later on */
		if (resp->resource_id_mask                ||
		    conn->xid_max + 1 < UINT16_C(1) << 18 ||
		    (conn->xid_max & (conn->xid_max + 1)) ||
		    resp->min_keycode < 8                 ||
		    resp->image_byte_order > 1            ||
		    resp->maximum_request_length < 4096   ||
		    resp->bitmap_format_bit_order > 1     ||
		    resp->bitmap_format_scanline_unit % 8 ||
		    resp->bitmap_format_scanline_pad % 8  ||
		    resp->bitmap_format_scanline_unit > resp->bitmap_format_scanline_pad)
			goto invalid;

		vendor_len          = resp->length_of_vendor;
		conn->info.nscreens = resp->number_of_roots;
		conn->info.nformats = resp->number_of_pixmap_formats;

		memmove(inbuf, resp->vendor, out_off = in_off = vendor_len);
		inbuf[out_off++] = '\0';
		out_off += (4 - out_off % 4) % 4;
		in_off += (4 - in_off % 4) % 4;
		in_off += offsetof(struct response, vendor);
		t = out_off;
		memmove(&inbuf[out_off], &inbuf[in_off], n - in_off);
		out_off += n - in_off;

		saved_errno = errno;
		new = realloc(inbuf, out_off);
		errno = saved_errno;
		if (new)
			inbuf = new;

		conn->info_buf     = inbuf;
		conn->info.vendor  = inbuf;
		conn->info.formats = (void *)&inbuf[t];
		conn->info.screens = (void *)&inbuf[t + conn->info.nformats * 8];
		conn->info.default_screen = conn->info.screens;

		ctx->in_buf_size = 0;
		ctx->in_buf = NULL;
		break;

	default:
	invalid:
		liberror_set_error("Invalid handshake response received from the display server",
				   "libaxl_receive_handshake", "libaxl", LIBAXL_ERROR_INVALID_HANDSHAKE_RESPONSE);
		errno = EBADMSG;
		return LIBAXL_ERROR_INVALID_HANDSHAKE_RESPONSE;
	}

	return (int)resp->status;
}
