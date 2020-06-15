/* See LICENSE file for copyright and license details. */
#include "common.h"

static const char *const req_formats[] = {
	/*
	 * . = 1 unused byte
	 * , = 2 unused bytes
	 * _ = 3 unused bytes
	 * ! = libaxl_bool_t
	 * 1 = uint8_t
	 * 2 = uint16_t
	 * 4 = uint32_t
	 * z = int8_t
	 * s = int16_t
	 * S = int32_t
	 * $ = previous marked length, in units
	 * % = previous marked format, in bits
	 * @ = non-encoded size_t length marked, align input to (size_t)
	 * u = STRING8, align input to (void *) and enter
	 * U = STRING16, align input to (void *) and enter
	 * d = data, uses %, align input to (void *) and enter
	 * e = event, align input to (union libaxl_event)
	 * ? = jump to special encoding routine
	 * * = following are repeated, align input to (void *) and enter
	 * | = following are included and encoded as uint32_t if corresponding bit is set in previous
	 * 
	 * The bytes 2–3 (starting at 0) are ignored here because its
	 * the length field and will be filled in by the function
	 */
	[LIBAXL_REQUEST_CREATE_WINDOW]              = "11,44ss222244|4444111.44!!,4444",
	[LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES]   = "1_44|4444111.44111.44!!,4444",
	[LIBAXL_REQUEST_GET_WINDOW_ATTRIBUTES]      = "1_4",
	[LIBAXL_REQUEST_DESTROY_WINDOW]             = "1_4",
	[LIBAXL_REQUEST_DESTROY_SUBWINDOWS]         = "1_4",
	[LIBAXL_REQUEST_CHANGE_SAVE_SET]            = "11,4",
	[LIBAXL_REQUEST_REPARENT_WINDOW]            = "1_44ss",
	[LIBAXL_REQUEST_MAP_WINDOW]                 = "1_4",
	[LIBAXL_REQUEST_MAP_SUBWINDOWS]             = "1_4",
	[LIBAXL_REQUEST_UNMAP_WINDOW]               = "1_4",
	[LIBAXL_REQUEST_UNMAP_SUBWINDOWS]           = "1_4",
	[LIBAXL_REQUEST_CONFIGURE_WINDOW]           = "1_42|,ss222,1",
	[LIBAXL_REQUEST_CIRCULATE_WINDOW]           = "11,4",
	[LIBAXL_REQUEST_GET_GEOMETRY]               = "1_4",
	[LIBAXL_REQUEST_QUERY_TREE]                 = "1_4",
	[LIBAXL_REQUEST_INTERN_ATOM]                = "1!,2$,u",
	[LIBAXL_REQUEST_GET_ATOM_NAME]              = "1_4",
	[LIBAXL_REQUEST_CHANGE_PROPERTY]            = "11,4441%_4$d",
	[LIBAXL_REQUEST_DELETE_PROPERTY]            = "11,44",
	[LIBAXL_REQUEST_GET_PROPERTY]               = "1_44444",
	[LIBAXL_REQUEST_LIST_PROPERTIES]            = "1_4",
	[LIBAXL_REQUEST_SET_SELECTION_OWNER]        = "1_444",
	[LIBAXL_REQUEST_GET_SELECTION_OWNER]        = "1_4",
	[LIBAXL_REQUEST_CONVERT_SELECTION]          = "1_4444",
	[LIBAXL_REQUEST_SEND_EVENT]                 = "1!,44e",
	[LIBAXL_REQUEST_GRAB_POINTER]               = "1!,4211444",
	[LIBAXL_REQUEST_UNGRAB_POINTER]             = "1_4",
	[LIBAXL_REQUEST_GRAB_BUTTON]                = "1_4211441.2",
	[LIBAXL_REQUEST_UNGRAB_BUTTON]              = "11,42,",
	[LIBAXL_REQUEST_CHANGE_ACTIVE_POINTER_GRAB] = "1_442,",
	[LIBAXL_REQUEST_GRAB_KEYBOARD]              = "1!,4411,",
	[LIBAXL_REQUEST_UNGRAB_KEYBOARD]            = "1_4",
	[LIBAXL_REQUEST_GRAB_KEY]                   = "1!,42111_",
	[LIBAXL_REQUEST_UNGRAB_KEY]                 = "11,42,",
	[LIBAXL_REQUEST_ALLOW_EVENTS]               = "11,4",
	[LIBAXL_REQUEST_GRAB_SERVER]                = "1_",
	[LIBAXL_REQUEST_UNGRAB_SERVER]              = "1_",
	[LIBAXL_REQUEST_QUERY_POINTER]              = "1_4",
	[LIBAXL_REQUEST_GET_MOTION_EVENTS]          = "1_444",
	[LIBAXL_REQUEST_TRANSLATE_COORDINATES]      = "1_44ss",
	[LIBAXL_REQUEST_WARP_POINTER]               = "1_44ss22ss",
	[LIBAXL_REQUEST_SET_INPUT_FOCUS]            = "11,44",
	[LIBAXL_REQUEST_GET_INPUT_FOCUS]            = "1_",
	[LIBAXL_REQUEST_QUERY_KEYMAP]               = "1_",
	[LIBAXL_REQUEST_OPEN_FONT]                  = "1_42$,u",
	[LIBAXL_REQUEST_CLOSE_FONT]                 = "1_4",
	[LIBAXL_REQUEST_QUERY_FONT]                 = "1_4",
	[LIBAXL_REQUEST_QUERY_TEXT_EXTENTS]         = "1_4@?U",
	[LIBAXL_REQUEST_LIST_FONTS]                 = "1_22$u",
	[LIBAXL_REQUEST_LIST_FONTS_WITH_INFO]       = "1_22$u",
	[LIBAXL_REQUEST_SET_FONT_PATH]              = "1_2$,*1$u",
	[LIBAXL_REQUEST_GET_FONT_PATH]              = "1_",
	[LIBAXL_REQUEST_CREATE_PIXMAP]              = "11,4422",
	[LIBAXL_REQUEST_FREE_PIXMAP]                = "11,4",
	[LIBAXL_REQUEST_CREATE_GC]                  = "1_444|1_444211111.44ss41!,ss4211",
	[LIBAXL_REQUEST_CHANGE_GC]                  = "1_44|1_444211111.44ss41!,ss4211",
	[LIBAXL_REQUEST_COPY_GC]                    = "1_444|1_444211111.44ss41!,ss4211",
	[LIBAXL_REQUEST_SET_DASHES]                 = "1_422$*1",
	[LIBAXL_REQUEST_SET_CLIP_RECTANGLES]        = "11,4ss@*ss22",
	[LIBAXL_REQUEST_FREE_GC]                    = "1_4",
	[LIBAXL_REQUEST_CLEAR_AREA]                 = "1!,4ss22",
	[LIBAXL_REQUEST_COPY_AREA]                  = "1_444ssss22",
	[LIBAXL_REQUEST_COPY_PLANE]                 = "1_444ssss224",
	[LIBAXL_REQUEST_POLY_POINT]                 = "11,44@*ss",
	[LIBAXL_REQUEST_POLY_LINE]                  = "11,44@*ss",
	[LIBAXL_REQUEST_POLY_SEGMENT]               = "1_44@*ssss",
	[LIBAXL_REQUEST_POLY_RECTANGLE]             = "1_44@*ss22",
	[LIBAXL_REQUEST_POLY_ARC]                   = "1_44@*ss22ss",
	[LIBAXL_REQUEST_FILL_POLY]                  = "1_4411,@*ss",
	[LIBAXL_REQUEST_POLY_FILL_RECTANGLE]        = "1_44@*ss22",
	[LIBAXL_REQUEST_POLY_FILL_ARC]              = "1_44@*ss22ss",
	[LIBAXL_REQUEST_PUT_IMAGE]                  = "11,4422ss11,@*1",
	[LIBAXL_REQUEST_GET_IMAGE]                  = "11,4ss224",
	[LIBAXL_REQUEST_POLY_TEXT8]                 = "1_44ss@*?1$zu\0""11111",
	[LIBAXL_REQUEST_POLY_TEXT16]                = "1_44ss@*?1$zU\0""11111",
	[LIBAXL_REQUEST_IMAGE_TEXT8]                = "11$,44ssu",
	[LIBAXL_REQUEST_IMAGE_TEXT16]               = "11$,44ssU",
	[LIBAXL_REQUEST_CREATE_COLORMAP]            = "11,444",
	[LIBAXL_REQUEST_FREE_COLORMAP]              = "1_4",
	[LIBAXL_REQUEST_COPY_COLORMAP_AND_FREE]     = "1_44",
	[LIBAXL_REQUEST_INSTALL_COLORMAP]           = "1_4",
	[LIBAXL_REQUEST_UNINSTALL_COLORMAP]         = "1_4",
	[LIBAXL_REQUEST_LIST_INSTALLED_COLORMAPS]   = "1_4",
	[LIBAXL_REQUEST_ALLOC_COLOR]                = "1_4222,",
	[LIBAXL_REQUEST_ALLOC_NAMED_COLOR]          = "1_42$,u",
	[LIBAXL_REQUEST_ALLOC_COLOR_CELLS]          = "1!,422",
	[LIBAXL_REQUEST_ALLOC_COLOR_PLANES]         = "1!,42222",
	[LIBAXL_REQUEST_FREE_COLORS]                = "1_44@*4",
	[LIBAXL_REQUEST_STORE_COLORS]               = "1_4@*42221.",
	[LIBAXL_REQUEST_STORE_NAMED_COLOR]          = "11,442$,u",
	[LIBAXL_REQUEST_QUERY_COLORS]               = "1_4@*4",
	[LIBAXL_REQUEST_LOOKUP_COLOR]               = "1_42$,u",
	[LIBAXL_REQUEST_CREATE_CURSOR]              = "1_4422222222",
	[LIBAXL_REQUEST_CREATE_GLYPH_CURSOR]        = "1_44422222222",
	[LIBAXL_REQUEST_FREE_CURSOR]                = "1_4",
	[LIBAXL_REQUEST_RECOLOR_CURSOR]             = "1_4222222",
	[LIBAXL_REQUEST_QUERY_BEST_SIZE]            = "11,422",
	[LIBAXL_REQUEST_QUERY_EXTENSION]            = "1_2$,u",
	[LIBAXL_REQUEST_LIST_EXTENSIONS]            = "1_",
	[LIBAXL_REQUEST_CHANGE_KEYBOARD_MAPPING]    = "11,11,?*4",
	[LIBAXL_REQUEST_GET_KEYBOARD_MAPPING]       = "1_11,",
	[LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL]    = "1_4|zzss1111",
	[LIBAXL_REQUEST_GET_KEYBOARD_CONTROL]       = "1_",
	[LIBAXL_REQUEST_BELL]                       = "1z,",
	[LIBAXL_REQUEST_CHANGE_POINTER_CONTROL]     = "1_sss!!",
	[LIBAXL_REQUEST_GET_POINTER_CONTROL]        = "1_",
	[LIBAXL_REQUEST_SET_SCREEN_SAVER]           = "1_ss11,",
	[LIBAXL_REQUEST_GET_SCREEN_SAVER]           = "1_",
	[LIBAXL_REQUEST_CHANGE_HOSTS]               = "11,1.2$*1",
	[LIBAXL_REQUEST_LIST_HOSTS]                 = "1_",
	[LIBAXL_REQUEST_SET_ACCESS_CONTROL]         = "11,",
	[LIBAXL_REQUEST_SET_CLOSE_DOWN_MODE]        = "11,",
	[LIBAXL_REQUEST_KILL_CLIENT]                = "1_4",
	[LIBAXL_REQUEST_ROTATE_PROPERTIES]          = "1_42$s*4",
	[LIBAXL_REQUEST_FORCE_SCREEN_SAVER]         = "11,",
	[LIBAXL_REQUEST_SET_POINTER_MAPPING]        = "11$,*1",
	[LIBAXL_REQUEST_GET_POINTER_MAPPING]        = "1_",
	[LIBAXL_REQUEST_SET_MODIFIER_MAPPING]       = "11$,*11",
	[LIBAXL_REQUEST_GET_MODIFIER_MAPPING]       = "1_",
	[LIBAXL_REQUEST_NO_OPERATION]               = "1_?"
};

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

/* TODO make it possible to send multiple request in the same syscall */
int
libaxl_send_request(LIBAXL_CONTEXT *restrict ctx, union libaxl_request_const_ptr request, int flags, uint16_t *restrict seqnump)
{
	LIBAXL_CONNECTION *conn = ctx->conn;
	LIBAXL_CONTEXT *pending, **pendingp;
	const char *req = request.as_voidptr;
	uint8_t code = *(const uint8_t *)req;
	const char *fmt, *repeat = NULL, *data;
	size_t i = 0, o = 0, j, n;
	size_t count = 0, format = 1, repcnt = 0;
	uint32_t mask;
	char *buf = ctx->out_buf, *subbuf, *new;
	size_t size = ctx->out_buf_size;
	uint16_t u16;
	uint32_t u32;

	RLOCK_CONNECTION_SEND(conn);
	pending = conn->pending_out;
	RUNLOCK_CONNECTION_SEND(conn);
	if (pending) {
		liberror_save_backtrace(NULL);
		liberror_set_error(pending == ctx
		                   ? "Request from the previous call is pending to be flush"
		                   : "A request from another thread is pending to be flushed",
		                   "libaxl_send_request", "errno", EALREADY);
		errno = EALREADY;
		return LIBAXL_ERROR_SYSTEM;
	}

	if (!code || (code > LIBAXL_REQUEST_GET_MODIFIER_MAPPING && code != LIBAXL_REQUEST_NO_OPERATION)) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Invalid request opcode", "libaxl_send_request", "libaxl",
		                   LIBAXL_ERROR_INVALID_REQUEST_OPCODE);
		errno = EINVAL;
		return LIBAXL_ERROR_INVALID_REQUEST_OPCODE;
	}

	fmt = req_formats[code];

again:
	for (;; fmt++) {
		if (o + 4 > size) {
			size += 32;
			new = liberror_realloc(buf, size);
			if (!new)
				return LIBAXL_ERROR_SYSTEM;
			ctx->out_buf = buf = new;
			ctx->out_buf_size = size;
		}

		switch (*fmt) {
		case '\0':
			if (repeat && --count) {
				fmt = repeat;
				goto again;
			}
			goto done;

		case '_':
			buf[o++] = 0; /* need not be 0 */
			i += 1;
			/* fall through */
		case ',':
			buf[o++] = 0; /* need not be 0 */
			i += 1;
			/* fall through */
		case '.':
			buf[o++] = 0; /* need not be 0 */
			i += 1;
			break;

		case '!':
			buf[o++] = !!req[i++];
			break;

		case '1':
			buf[o++] = req[i++];
			break;

		case '2':
			*(uint16_t *)&buf[o] = htons(*(const uint16_t *)&req[i]);
			i += 2;
			o += 2;
			break;

		case '4':
			*(uint32_t *)&buf[o] = htonl(*(const uint32_t *)&req[i]);
			i += 4;
			o += 4;
			break;

		case 'z':
			buf[o] = req[i];
			TWOS_COMPLEMENT8(&buf[o]);
			i += 1;
			o += 1;
			break;

		case 's':
			u16 = *(const uint16_t *)&req[i];
			TWOS_COMPLEMENT16(&u16);
			*(uint16_t *)&buf[o] = htons(u16);
			i += 2;
			o += 2;
			break;

		case 'S':
			u32 = *(const uint32_t *)&req[i];
			TWOS_COMPLEMENT32(&u32);
			*(uint32_t *)&buf[o] = htonl(u32);
			i += 4;
			o += 4;
			break;

		case '$':
			if (fmt[-1] == '2')
				count = (size_t)*(const uint16_t *)&req[i - 2];
			else if (fmt[-1] == '1')
				count = (size_t)*(const uint8_t *)&req[i - 1];
			else
				count = (size_t)*(const uint32_t *)&req[i - 4];
			break;

		case '%':
			if (fmt[-1] == '1')
				format = (size_t)*(const uint8_t *)&req[i - 1];
			else if (fmt[-1] == '2')
				format = (size_t)*(const uint16_t *)&req[i - 2];
			else
				format = (size_t)*(const uint32_t *)&req[i - 4];
			break;

		case '@':
			ALIGN(&i, size_t);
			count = *(const size_t *)&req[i - 2];
			break;

		case 'u':
			format = 8;
			goto case_d;

		case 'U':
			format = 16;
			goto case_d;

		case 'd':
		case_d:
			ALIGN(&i, void *);
			data = *(const char *const *)&req[i];
			count *= format / 8;
			if (o + count > size) {
				size += (count & 3) ? (count | 3) + 1 : count;
				new = liberror_realloc(buf, size);
				if (!new)
					return LIBAXL_ERROR_SYSTEM;
				ctx->out_buf = buf = new;
				ctx->out_buf_size = size;
			}
			subbuf = &buf[o];
			if (format == 8) {
				for (j = 0; j < count; j += 1)
					*(uint8_t *)&subbuf[j] = *(const uint8_t *)&data[j];
			} else if (format == 16) {
				for (j = 0; j < count; j += 2)
					*(uint16_t *)&subbuf[j] = htons(*(const uint16_t *)&data[j]);
			} else if (format == 32) {
				for (j = 0; j < count; j += 4)
					*(uint32_t *)&subbuf[j] = htonl(*(const uint32_t *)&data[j]);
			} else if (format != 0) {
				liberror_save_backtrace(NULL);
				liberror_set_error("Invalid format number", "libaxl_send_request", "libaxl",
						   LIBAXL_ERROR_INVALID_FORMAT_NUMBER);
				errno = EINVAL;
				return LIBAXL_ERROR_INVALID_FORMAT_NUMBER;
			}
			o += count;
			i += count;
			break;

		case 'e': /* TODO event */
			ALIGN(&i, union libaxl_event);
			fprintf(stderr, "libaxl_send_request: function not fully implemented: 'e' case\n");
			abort();
			break;

		case '?':
			fmt++;
			goto special_encoding;

		case '*':
			repcnt = count;
			if (!repcnt)
				goto done;
			ALIGN(&i, void *);
			req = *(const char *const *)&req[i];
			repeat = &fmt[1];
			i = 0;
			break;

		case '|':
			if (fmt[-1] == '4')
				mask = *(const uint32_t *)&req[i - 4];
			else if (fmt[-1] == '2')
				mask = (uint32_t)*(const uint16_t *)&req[i - 2];
			else
				mask = (uint32_t)*(const uint8_t *)&req[i - 1];
			for (fmt++;; fmt++) {
				if (o + 4 > size) {
					size += 32;
					new = liberror_realloc(buf, size);
					if (!new)
						return LIBAXL_ERROR_SYSTEM;
					ctx->out_buf = buf = new;
					ctx->out_buf_size = size;
				}

				switch (*fmt) {
				case '\0':
					goto done;

				case '.':
					i += 1;
					break;

				case ',':
					i += 2;
					break;

				case '_':
					i += 3;
					break;

				case '!':
					if (mask & 1) {
						*(uint32_t *)&buf[o] = htonl((uint32_t)(req[i] ? 1 : 0));
						o += 4;
					}
					mask >>= 1;
					i += 1;
					break;

				case '1':
				case 'z':
					if (mask & 1) {
						*(uint32_t *)&buf[o] = htonl((uint32_t)*(const uint8_t *)&req[i]);
						if (*fmt == 'z')
							TWOS_COMPLEMENT8(&buf[o]);
						o += 4;
					}
					mask >>= 1;
					i += 1;
					break;

				case '2':
				case 's':
					if (mask & 1) {
						u16 = *(const uint16_t *)&req[i];
						if (*fmt == 's')
							TWOS_COMPLEMENT16(&u16);
						*(uint32_t *)&buf[o] = htonl((uint32_t)u16);
						o += 4;
					}
					mask >>= 1;
					i += 2;
					break;

				case '4':
				case 'S':
					if (mask & 1) {
						u32 = *(const uint16_t *)&req[i];
						if (*fmt == 'S')
							TWOS_COMPLEMENT32(&u32);
						*(uint32_t *)&buf[o] = htonl(u32);
						o += 4;
					}
					mask >>= 1;
					i += 4;
					break;

				default:
					abort();
				};
			}

		default:
			abort();
		}
	}

special_encoding:
	switch (code) {
	case LIBAXL_REQUEST_QUERY_TEXT_EXTENTS:
		buf[2] = (count & 1); /* _odd_length */
		break;

	case LIBAXL_REQUEST_CHANGE_KEYBOARD_MAPPING:
		count  = (size_t)((const union libaxl_request *)req)->change_keyboard_mapping.keycode_count;
		count *= (size_t)((const union libaxl_request *)req)->change_keyboard_mapping.keysyms_per_keycode;
		goto again;

	case LIBAXL_REQUEST_POLY_TEXT8:
	case LIBAXL_REQUEST_POLY_TEXT16:
		if (((const uint8_t *)req)[i] == LIBAXL_FONT_SHIFT_INDICATOR)
			while (*fmt++);
		goto again;

	case LIBAXL_REQUEST_NO_OPERATION:
		if (!((const union libaxl_request *)req)->_request_length) {
			liberror_save_backtrace(NULL);
			liberror_set_error("Malformatted request: request length most be at least 1 byte-quad",
			                   "libaxl_send_request", "libaxl", LIBAXL_ERROR_MALFORMATTED_REQUEST);
			errno = EINVAL;
			return LIBAXL_ERROR_MALFORMATTED_REQUEST;
		}
		o = 4 * (size_t)((const union libaxl_request *)req)->_request_length;
		if (o > size) {
			new = liberror_realloc(buf, o);
			if (!new)
				return LIBAXL_ERROR_SYSTEM;
			ctx->out_buf = buf = new;
			ctx->out_buf_size = size = o;
			memset(&buf[4], 0, o - 4);
		}
		break;

	default:
		abort();
	}

done:
	if (o & 3) {
		n = o;
		o = (o | 3) + 1;
		if (o > size) {
			new = liberror_realloc(buf, o);
			if (!new)
				return LIBAXL_ERROR_SYSTEM;
			ctx->out_buf = buf = new;
			ctx->out_buf_size = o;
			memset(&buf[n], 0, o - n);
		}
	}
	n = o / 4;
	if (n > UINT16_MAX) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Message is too long, cannot be longer than 65535 byte-quads",
		                   "libaxl_send_request", "errno", EMSGSIZE);
		errno = EMSGSIZE;
		return LIBAXL_ERROR_SYSTEM;
	}
	*(uint16_t *)&buf[2] = htons((uint16_t)n); /* _request_length */
	ctx->out_length = o;
	ctx->out_progress = 0;

	WLOCK_CONNECTION_SEND(conn);

	*seqnump = ++conn->last_seqnum;
	conn->request_map[*seqnump] = code;
	if (send_all(conn->fd, ctx->out_buf, ctx->out_length, flags, &ctx->out_progress)) {
		ctx->next_pending_out = NULL;
		pendingp = &conn->pending_out;
		while (*pendingp)
			pendingp = &(*pendingp)->next_pending_out;
		*pendingp = ctx;
		ctx->refcount += 1;

		WUNLOCK_CONNECTION_SEND(conn);

		liberror_save_backtrace(NULL);
		liberror_set_error("Request has been buffered and is ready to be sent",
		                   "libaxl_send_request", "errno", EINPROGRESS);
		errno = EINPROGRESS;
		return LIBAXL_ERROR_SYSTEM;
	}

	WUNLOCK_CONNECTION_SEND(conn);

	return 0;
}
