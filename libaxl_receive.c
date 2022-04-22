/* See LICENSE file for copyright and license details. */
#include "common.h"

static const char *const event_formats[] = {
	/*
	 * . = 1 unused byte
	 * , = 2 unused bytes
	 * _ = 3 unused bytes
	 * - = 4 unused bytes
	 * # = 32 uint8_t
	 * ! = libaxl_bool_t
	 * 1 = uint8_t
	 * 2 = uint16_t
	 * 4 = uint32_t
	 * z = int8_t
	 * s = int16_t
	 * S = int32_t
	 * ? = special encoding
	 */
	[LIBAXL_ERROR]                   = "112421",
	[LIBAXL_REPLY]                   = "?",
	[LIBAXL_EVENT_KEY_PRESS]         = "1124444ssss2!",
	[LIBAXL_EVENT_KEY_RELEASE]       = "1124444ssss2!",
	[LIBAXL_EVENT_BUTTON_PRESS]      = "1124444ssss2!",
	[LIBAXL_EVENT_BUTTON_RELEASE]    = "1124444ssss2!",
	[LIBAXL_EVENT_MOTION_NOTIFY]     = "1124444ssss2!",
	[LIBAXL_EVENT_ENTER_NOTIFY]      = "1124444ssss211",
	[LIBAXL_EVENT_LEAVE_NOTIFY]      = "1124444ssss211",
	[LIBAXL_EVENT_FOCUS_IN]          = "112411",
	[LIBAXL_EVENT_FOCUS_OUT]         = "112411",
	[LIBAXL_EVENT_KEYMAP_NOTIFY]     = "#",
	[LIBAXL_EVENT_EXPOSE]            = "1.2422222",
	[LIBAXL_EVENT_GRAPHICS_EXPOSURE] = "1.242222221",
	[LIBAXL_EVENT_NO_EXPOSURE]       = "1.242",
	[LIBAXL_EVENT_VISIBILITY_NOTIFY] = "1.241",
	[LIBAXL_EVENT_CREATE_NOTIFY]     = "1.244ss222!",
	[LIBAXL_EVENT_DESTROY_NOTIFY]    = "1.244",
	[LIBAXL_EVENT_UNMAP_NOTIFY]      = "1.244!",
	[LIBAXL_EVENT_MAP_NOTIFY]        = "1.244!",
	[LIBAXL_EVENT_MAP_REQUEST]       = "1.244",
	[LIBAXL_EVENT_REPARENT_NOTIFY]   = "1.2444ss!",
	[LIBAXL_EVENT_CONFIGURE_NOTIFY]  = "1.2444ss222!",
	[LIBAXL_EVENT_CONFIGURE_REQUEST] = "112444ss2222",
	[LIBAXL_EVENT_GRAVITY_NOTIFY]    = "1.244ss",
	[LIBAXL_EVENT_RESIZE_REQUEST]    = "1.2422",
	[LIBAXL_EVENT_CIRCULATE_NOTIFY]  = "1.244-1",
	[LIBAXL_EVENT_CIRCULATE_REQUEST] = "1.244-1",
	[LIBAXL_EVENT_PROPERTY_NOTIFY]   = "1.2441",
	[LIBAXL_EVENT_SELECTION_CLEAR]   = "1.2444",
	[LIBAXL_EVENT_SELECTION_REQUEST] = "1.2444444",
	[LIBAXL_EVENT_SELECTION_NOTIFY]  = "1.244444",
	[LIBAXL_EVENT_COLORMAP_NOTIFY]   = "1.244!1",
	[LIBAXL_EVENT_CLIENT_MESSAGE]    = "11244",
	[LIBAXL_EVENT_MAPPING_NOTIFY]    = "1.2111"
};

static const char *const reply_formats[] = {
	/*
	 * = = 8 unused bytes
	 * $ = previous marked length, in units
	 * % = previous marked format, in bits
	 * @ = non-encoded size_t length marked, align output to (size_t)
	 * u = STRING8, align output to (void *) and enter (equivalent to "*1/")
	 * U = STRING16, align output to (void *) and enter (equivalent to "*2/")
	 * d = data, uses %, align output to (void *) and enter
	 * * = following are repeated, align output to (void *) and enter
	 * & = * but requires allocation (there is only support for use once) (choose padding after alignment)
	 * / = end of * or &, for & unless finished realigned output and start over
	 * p = padding, align input to byte-quad
	 */
	[0]                                         = NULL,
	[LIBAXL_REQUEST_CREATE_WINDOW]              = NULL,
	[LIBAXL_REQUEST_CHANGE_WINDOW_ATTRIBUTES]   = NULL,
	[LIBAXL_REQUEST_GET_WINDOW_ATTRIBUTES]      = "1124421144!!1!4442",
	[LIBAXL_REQUEST_DESTROY_WINDOW]             = NULL,
	[LIBAXL_REQUEST_DESTROY_SUBWINDOWS]         = NULL,
	[LIBAXL_REQUEST_CHANGE_SAVE_SET]            = NULL,
	[LIBAXL_REQUEST_REPARENT_WINDOW]            = NULL,
	[LIBAXL_REQUEST_MAP_WINDOW]                 = NULL,
	[LIBAXL_REQUEST_MAP_SUBWINDOWS]             = NULL,
	[LIBAXL_REQUEST_UNMAP_WINDOW]               = NULL,
	[LIBAXL_REQUEST_UNMAP_SUBWINDOWS]           = NULL,
	[LIBAXL_REQUEST_CONFIGURE_WINDOW]           = NULL,
	[LIBAXL_REQUEST_CIRCULATE_WINDOW]           = NULL,
	[LIBAXL_REQUEST_GET_GEOMETRY]               = "1244ss222",
	[LIBAXL_REQUEST_QUERY_TREE]                 = "1.24442$=-,*4/",
	[LIBAXL_REQUEST_INTERN_ATOM]                = "1.244",
	[LIBAXL_REQUEST_GET_ATOM_NAME]              = "1.242$==-,u",
	[LIBAXL_REQUEST_CHANGE_PROPERTY]            = NULL,
	[LIBAXL_REQUEST_DELETE_PROPERTY]            = NULL,
	[LIBAXL_REQUEST_GET_PROPERTY]               = "11%24444$=-d",
	[LIBAXL_REQUEST_LIST_PROPERTIES]            = "1.242$==-,*4/",
	[LIBAXL_REQUEST_SET_SELECTION_OWNER]        = NULL,
	[LIBAXL_REQUEST_GET_SELECTION_OWNER]        = "1.244",
	[LIBAXL_REQUEST_CONVERT_SELECTION]          = NULL,
	[LIBAXL_REQUEST_SEND_EVENT]                 = NULL,
	[LIBAXL_REQUEST_GRAB_POINTER]               = "1124",
	[LIBAXL_REQUEST_UNGRAB_POINTER]             = NULL,
	[LIBAXL_REQUEST_GRAB_BUTTON]                = NULL,
	[LIBAXL_REQUEST_UNGRAB_BUTTON]              = NULL,
	[LIBAXL_REQUEST_CHANGE_ACTIVE_POINTER_GRAB] = NULL,
	[LIBAXL_REQUEST_GRAB_KEYBOARD]              = "1124",
	[LIBAXL_REQUEST_UNGRAB_KEYBOARD]            = NULL,
	[LIBAXL_REQUEST_GRAB_KEY]                   = NULL,
	[LIBAXL_REQUEST_UNGRAB_KEY]                 = NULL,
	[LIBAXL_REQUEST_ALLOW_EVENTS]               = NULL,
	[LIBAXL_REQUEST_GRAB_SERVER]                = NULL,
	[LIBAXL_REQUEST_UNGRAB_SERVER]              = NULL,
	[LIBAXL_REQUEST_QUERY_POINTER]              = ".!2444ssss2",
	[LIBAXL_REQUEST_GET_MOTION_EVENTS]          = "1!244$==-*4ss/",
	[LIBAXL_REQUEST_TRANSLATE_COORDINATES]      = "1!244ss",
	[LIBAXL_REQUEST_WARP_POINTER]               = NULL,
	[LIBAXL_REQUEST_SET_INPUT_FOCUS]            = NULL,
	[LIBAXL_REQUEST_GET_INPUT_FOCUS]            = "11244",
	[LIBAXL_REQUEST_QUERY_KEYMAP]               = "1.24#",
	[LIBAXL_REQUEST_OPEN_FONT]                  = NULL,
	[LIBAXL_REQUEST_CLOSE_FONT]                 = NULL,
	[LIBAXL_REQUEST_QUERY_FONT]                 = "1.24sssss2-sssss2-2222$111!ss4$*44/*sssss2/",
	[LIBAXL_REQUEST_QUERY_TEXT_EXTENTS]         = "1124ssssSSS",
	[LIBAXL_REQUEST_LIST_FONTS]                 = "1.242$==-,&1$u/",
	[LIBAXL_REQUEST_LIST_FONTS_WITH_INFO]       = "11$24?sssss2-sssss2-2222$?111!ss4*44/u",
	[LIBAXL_REQUEST_SET_FONT_PATH]              = NULL,
	[LIBAXL_REQUEST_GET_FONT_PATH]              = "1.242$==-,&1$u/",
	[LIBAXL_REQUEST_CREATE_PIXMAP]              = NULL,
	[LIBAXL_REQUEST_FREE_PIXMAP]                = NULL,
	[LIBAXL_REQUEST_CREATE_GC]                  = NULL,
	[LIBAXL_REQUEST_CHANGE_GC]                  = NULL,
	[LIBAXL_REQUEST_COPY_GC]                    = NULL,
	[LIBAXL_REQUEST_SET_DASHES]                 = NULL,
	[LIBAXL_REQUEST_SET_CLIP_RECTANGLES]        = NULL,
	[LIBAXL_REQUEST_FREE_GC]                    = NULL,
	[LIBAXL_REQUEST_CLEAR_AREA]                 = NULL,
	[LIBAXL_REQUEST_COPY_AREA]                  = NULL,
	[LIBAXL_REQUEST_COPY_PLANE]                 = NULL,
	[LIBAXL_REQUEST_POLY_POINT]                 = NULL,
	[LIBAXL_REQUEST_POLY_LINE]                  = NULL,
	[LIBAXL_REQUEST_POLY_SEGMENT]               = NULL,
	[LIBAXL_REQUEST_POLY_RECTANGLE]             = NULL,
	[LIBAXL_REQUEST_POLY_ARC]                   = NULL,
	[LIBAXL_REQUEST_FILL_POLY]                  = NULL,
	[LIBAXL_REQUEST_POLY_FILL_RECTANGLE]        = NULL,
	[LIBAXL_REQUEST_POLY_FILL_ARC]              = NULL,
	[LIBAXL_REQUEST_PUT_IMAGE]                  = NULL,
	[LIBAXL_REQUEST_GET_IMAGE]                  = "11244==-@u",
	[LIBAXL_REQUEST_POLY_TEXT8]                 = NULL,
	[LIBAXL_REQUEST_POLY_TEXT16]                = NULL,
	[LIBAXL_REQUEST_IMAGE_TEXT8]                = NULL,
	[LIBAXL_REQUEST_IMAGE_TEXT16]               = NULL,
	[LIBAXL_REQUEST_CREATE_COLORMAP]            = NULL,
	[LIBAXL_REQUEST_FREE_COLORMAP]              = NULL,
	[LIBAXL_REQUEST_COPY_COLORMAP_AND_FREE]     = NULL,
	[LIBAXL_REQUEST_INSTALL_COLORMAP]           = NULL,
	[LIBAXL_REQUEST_UNINSTALL_COLORMAP]         = NULL,
	[LIBAXL_REQUEST_LIST_INSTALLED_COLORMAPS]   = "1.242$==-,*4/",
	[LIBAXL_REQUEST_ALLOC_COLOR]                = "1.24222,4",
	[LIBAXL_REQUEST_ALLOC_NAMED_COLOR]          = "1.244222222",
	[LIBAXL_REQUEST_ALLOC_COLOR_CELLS]          = "1.242$2$==-*4/*4/",
	[LIBAXL_REQUEST_ALLOC_COLOR_PLANES]         = "1.242$,444=*4",
	[LIBAXL_REQUEST_FREE_COLORS]                = NULL,
	[LIBAXL_REQUEST_STORE_COLORS]               = NULL,
	[LIBAXL_REQUEST_STORE_NAMED_COLOR]          = NULL,
	[LIBAXL_REQUEST_QUERY_COLORS]               = "1.242$==-,*222,/",
	[LIBAXL_REQUEST_LOOKUP_COLOR]               = "1.24222222",
	[LIBAXL_REQUEST_CREATE_CURSOR]              = NULL,
	[LIBAXL_REQUEST_CREATE_GLYPH_CURSOR]        = NULL,
	[LIBAXL_REQUEST_FREE_CURSOR]                = NULL,
	[LIBAXL_REQUEST_RECOLOR_CURSOR]             = NULL,
	[LIBAXL_REQUEST_QUERY_BEST_SIZE]            = "1.2422",
	[LIBAXL_REQUEST_QUERY_EXTENSION]            = "1.24!1111",
	[LIBAXL_REQUEST_LIST_EXTENSIONS]            = "11$24===&1$u/",
	[LIBAXL_REQUEST_CHANGE_KEYBOARD_MAPPING]    = NULL,
	[LIBAXL_REQUEST_GET_KEYBOARD_MAPPING]       = "1124$===*4/",
	[LIBAXL_REQUEST_CHANGE_KEYBOARD_CONTROL]    = NULL,
	[LIBAXL_REQUEST_GET_KEYBOARD_CONTROL]       = "112441122,#",
	[LIBAXL_REQUEST_BELL]                       = NULL,
	[LIBAXL_REQUEST_CHANGE_POINTER_CONTROL]     = NULL,
	[LIBAXL_REQUEST_GET_POINTER_CONTROL]        = "1.24222",
	[LIBAXL_REQUEST_SET_SCREEN_SAVER]           = NULL,
	[LIBAXL_REQUEST_GET_SCREEN_SAVER]           = "1.242211",
	[LIBAXL_REQUEST_CHANGE_HOSTS]               = NULL,
	[LIBAXL_REQUEST_LIST_HOSTS]                 = "1124$2==-,&1.2$up/",
	[LIBAXL_REQUEST_SET_ACCESS_CONTROL]         = NULL,
	[LIBAXL_REQUEST_SET_CLOSE_DOWN_MODE]        = NULL,
	[LIBAXL_REQUEST_KILL_CLIENT]                = NULL,
	[LIBAXL_REQUEST_ROTATE_PROPERTIES]          = NULL,
	[LIBAXL_REQUEST_FORCE_SCREEN_SAVER]         = NULL,
	[LIBAXL_REQUEST_SET_POINTER_MAPPING]        = "1124",
	[LIBAXL_REQUEST_GET_POINTER_MAPPING]        = "11$24===*1/",
	[LIBAXL_REQUEST_SET_MODIFIER_MAPPING]       = "1124",
	[LIBAXL_REQUEST_GET_MODIFIER_MAPPING]       = "11$24===*11/",
	[LIBAXL_REQUEST_NO_OPERATION]               = NULL
};

static size_t
calculate_struct_size(const char *fmt, size_t *alignmentp)
{
	size_t size = 0, i;
	*alignmentp = 1;
	for (;; fmt++) {
		switch (*fmt) {
		case '?':
		case '$':
		case '%':
		case 'p':
			break;

		case '.':
		case '!':
		case '1':
		case 'z':
			size += 1;
			break;

		case ',':
		case '2':
		case 's':
			*alignmentp = MAX(*alignmentp, 2);
			size += 2;
			break;

		case '_':
			size += 3;
			break;

		case '-':
		case '4':
		case 'S':
			*alignmentp = MAX(*alignmentp, 4);
			size += 4;
			break;

		case '=':
			*alignmentp = MAX(*alignmentp, 4); /* 2 uint32_t, not 1 uint64_t */
			size += 8;
			break;

		case '#':
			size += 32;
			break;

		case '@':
			*alignmentp = MAX(*alignmentp, sizeof(size_t));
			ALIGN(&size, size_t);
			size += sizeof(size_t);
			break;

		case '*':
			for (i = 0;; fmt++) {
				if (*fmt == '*') {
					i += 1;
				} else if (*fmt == '/') {
					if (!--i)
						break;
				} else if (!*fmt) {
					abort();
				}
			}
			/* fall through */

		case 'u':
		case 'U':
		case 'd':
			*alignmentp = MAX(*alignmentp, sizeof(void *));
			ALIGN(&size, void *);
			size += sizeof(void *);
			break;

		case '/':
			return size;

		default:
			abort();
		}
	}
}

/* XXX make it possible to prefetch pending messages */
int
libaxl_receive(LIBAXL_CONTEXT *restrict ctx, union libaxl_input *restrict msgp, int flags)
{
	struct {
		const char *fmt;
		char *msg;
		size_t ic, oc, o, count;
	} stack[3];
	size_t si = 0;
	LIBAXL_CONNECTION *conn = ctx->conn;
	const char *fmt;
	char *restrict msg = (char *)msgp;
	char *restrict inbuf, *data;
	size_t format = 1, counts[] = {0, 0, 0}, count = 0;
	ssize_t r;
	uint64_t n, u64;
	uint8_t code;
	size_t t, i, j, o, ic = 0, oc = 0, size, alignment = 1;
	int qc = 0;
#ifdef MSG_TRUNC
	int flag_trunc;

	flags ^= flag_trunc = flags & MSG_TRUNC;
#endif

	WLOCK_CONNECTION_RECV(conn);

	inbuf = conn->in_buf;
	n = 32;

	if (conn->in_buf_size < n) {
		inbuf = liberror_realloc(inbuf, n);
		if (!inbuf) {
			WUNLOCK_CONNECTION_RECV(conn);
			return LIBAXL_ERROR_SYSTEM;
		}
		conn->in_buf = inbuf;
		conn->in_buf_size = n;
	}

	while (conn->in_progress < n) {
		r = recv(conn->fd, &inbuf[conn->in_progress], n - conn->in_progress, flags);
		if (r <= 0) {
			liberror_save_backtrace(NULL);
			if (!r) {
				liberror_set_error("The connection to the display server has been closed",
				                   "libaxl_receive", "libaxl", LIBAXL_ERROR_CONNECTION_CLOSED);
				WUNLOCK_CONNECTION_RECV(conn);
				return LIBAXL_ERROR_CONNECTION_CLOSED;
			}
			liberror_recv_failed(conn->fd, &inbuf[conn->in_progress], n - conn->in_progress, flags, "<display server>");
			WUNLOCK_CONNECTION_RECV(conn);
			return LIBAXL_ERROR_SYSTEM;
		}
		conn->in_progress += (size_t)r;
	}

	code = *(uint8_t *)inbuf;
	code &= ~LIBAXL_SYNTHETIC_EVENT_BIT;

	if (code == LIBAXL_REPLY) {
		n = (uint64_t)ntohl(*(uint32_t *)&inbuf[4]);
		n = 4 * n + 32;
		if (n > SIZE_MAX) {
			WUNLOCK_CONNECTION_RECV(conn);
			liberror_save_backtrace(NULL);
			liberror_set_error("Received message is too large to allocate",
			                   "libaxl_receive", "libaxl", LIBAXL_ERROR_SYSTEM);
			errno = ENOMEM;
			return LIBAXL_ERROR_SYSTEM;
		}
		if (conn->in_buf_size < n) {
			inbuf = liberror_realloc(inbuf, n);
			if (!inbuf) {
				WUNLOCK_CONNECTION_RECV(conn);
				return LIBAXL_ERROR_SYSTEM;
			}
			conn->in_buf = inbuf;
			conn->in_buf_size = n;
		}
		while (conn->in_progress < n) {
			r = recv(conn->fd, &inbuf[conn->in_progress], n - conn->in_progress, flags);
			if (r <= 0) {
				liberror_save_backtrace(NULL);
				if (!r) {
					liberror_set_error("The connection to the display server has been closed",
					                   "libaxl_receive", "libaxl", LIBAXL_ERROR_CONNECTION_CLOSED);
					WUNLOCK_CONNECTION_RECV(conn);
					return LIBAXL_ERROR_CONNECTION_CLOSED;
				}
				liberror_recv_failed(conn->fd, &inbuf[conn->in_progress], n - conn->in_progress,
				                     flags, "<display server>");
				WUNLOCK_CONNECTION_RECV(conn);
				return LIBAXL_ERROR_SYSTEM;
			}
			conn->in_progress += (size_t)r;
		}
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

	if (code > sizeof(event_formats) / sizeof(*event_formats) ||
	    !(fmt = event_formats[code])) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Received message's code is invalid", "libaxl_receive", "libaxl", LIBAXL_ERROR_SYSTEM);
		errno = EBADMSG;
		return LIBAXL_ERROR_SYSTEM;
	}

	for (i = 0; i < n; fmt++) {
		switch (*fmt) {
		case '\0':
			goto end_of_fmt;

		case '.':
			i += 1;
			break;

		case ',':
			i += 2;
			break;

		case '_':
			i += 3;
			break;

		case '-':
			i += 4;
			break;

		case '#':
			*(uint64_t *)&msg[i +  0] = *(uint64_t *)&inbuf[i +  0];
			*(uint64_t *)&msg[i +  8] = *(uint64_t *)&inbuf[i +  8];
			*(uint64_t *)&msg[i + 16] = *(uint64_t *)&inbuf[i + 16];
			*(uint64_t *)&msg[i + 24] = *(uint64_t *)&inbuf[i + 24];
			i += 32;
			break;

		case '!':
		case '1':
			*(uint8_t *)&msg[i] = *(uint8_t *)&inbuf[i];
			i += 1;
			break;

		case '2':
			if (i + 2 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint16_t *)&msg[i] = ntohs(*(uint16_t *)&inbuf[i]);
			i += 2;
			break;

		case '4':
			if (i + 4 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint32_t *)&msg[i] = ntohl(*(uint32_t *)&inbuf[i]);
			i += 4;
			break;

		case 'z':
			*(uint8_t *)&msg[i] = *(uint8_t *)&inbuf[i];
			UNTWOS_COMPLEMENT8(&msg[i]);
			i += 1;
			break;

		case 's':
			if (i + 2 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint16_t *)&msg[i] = ntohs(*(uint16_t *)&inbuf[i]);
			UNTWOS_COMPLEMENT16(&msg[i]);
			i += 2;
			break;

		case 'S':
			if (i + 4 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint32_t *)&msg[i] = ntohl(*(uint32_t *)&inbuf[i]);
			UNTWOS_COMPLEMENT32(&msg[i]);
			i += 4;
			break;

		case '?':
			/* We know it is LIBAXL_REPLY message */
			goto received_reply;

		default:
			abort();
		}
	}

	if (*fmt) {
		liberror_save_backtrace(NULL);
		goto short_msg;
	}

end_of_fmt:
	return 0;

received_reply:
	code = conn->request_map[ntohs(*(uint16_t *)&inbuf[2])]; /* read-lock here is pointless */
	fmt = reply_formats[code];
	if (!fmt) {
		liberror_set_error("Received reply message with unrecognised opcode",
		                   "libaxl_receive", "libaxl", LIBAXL_ERROR_INVALID_REPLY_OPCODE);
		errno = EBADMSG;
		return LIBAXL_ERROR_INVALID_REPLY_OPCODE;
	}

	for (i = o = 0; i < n || *fmt == '@' || *fmt == '$' || *fmt == '%' || *fmt == '/'; fmt++) {
		switch (*fmt) {
		case '\0':
			goto end_of_fmt;

		case '.':
			i += 1;
			o += 1;
			break;

		case ',':
			i += 2;
			o += 2;
			break;

		case '_':
			i += 3;
			o += 3;
			break;

		case '-':
			i += 4;
			o += 4;
			break;

		case '=':
			i += 8;
			o += 8;
			break;

		case '#':
			*(uint64_t *)&msg[o +  0] = *(uint64_t *)&inbuf[i +  0];
			*(uint64_t *)&msg[o +  8] = *(uint64_t *)&inbuf[i +  8];
			*(uint64_t *)&msg[o + 16] = *(uint64_t *)&inbuf[i + 16];
			*(uint64_t *)&msg[o + 24] = *(uint64_t *)&inbuf[i + 24];
			i += 32;
			o += 32;
			break;

		case '!':
		case '1':
			*(uint8_t *)&msg[o++] = *(uint8_t *)&inbuf[i++];
			break;

		case '2':
			if (i + 2 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint16_t *)&msg[o] = ntohs(*(uint16_t *)&inbuf[i]);
			i += 2;
			o += 2;
			break;

		case '4':
			if (i + 4 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint32_t *)&msg[o] = ntohl(*(uint32_t *)&inbuf[i]);
			i += 4;
			o += 4;
			break;

		case 'z':
			*(uint8_t *)&msg[o] = *(uint8_t *)&inbuf[i];
			UNTWOS_COMPLEMENT8(&msg[o]);
			i += 1;
			o += 1;
			break;

		case 's':
			if (i + 2 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint16_t *)&msg[o] = ntohs(*(uint16_t *)&inbuf[i]);
			UNTWOS_COMPLEMENT16(&msg[o]);
			i += 2;
			o += 2;
			break;

		case 'S':
			if (i + 4 > n) {
				liberror_save_backtrace(NULL);
				goto short_msg;
			}
			*(uint32_t *)&msg[o] = ntohl(*(uint32_t *)&inbuf[i]);
			UNTWOS_COMPLEMENT32(&msg[o]);
			i += 4;
			o += 4;
			break;

		case '%':
			if (fmt[-1] == '1')
				format = (size_t)*(uint8_t *)&msg[i - 1];
			else if (fmt[-1] == '2')
				format = (size_t)*(uint16_t *)&msg[i - 2];
			else
				format = (size_t)*(uint32_t *)&msg[i - 4];
			break;

		case '@':
			ALIGN(&o, size_t);
			u64 = 4 * (uint64_t)*(uint32_t *)&msg[4];
			if (u64 > SIZE_MAX) {
				liberror_save_backtrace(NULL);
				goto corrupt_reply;
			}
			*(size_t *)&msg[o] = counts[ic++] = (size_t)u64;
			o += sizeof(size_t);
			break;

		case '$':
			if (fmt[-1] == '2')
				counts[ic++] = (size_t)*(uint16_t *)&msg[i - 2];
			else if (fmt[-1] == '1')
				counts[ic++] = (size_t)*(uint8_t *)&msg[i - 1];
			else
				counts[ic++] = (size_t)*(uint32_t *)&msg[i - 4];
			break;

		case 'p':
			ALIGN(&i, uint32_t);
			break;

		case 'u':
			format = 8;
			goto case_d;

		case 'U':
			format = 16;
			goto case_d;

		case 'd':
		case_d:
			ALIGN(&o, void *);
			*(void **)&msg[o] = data = &inbuf[i];
			count = counts[oc++];
			count *= format / 8;
			if (format == 16) {
				for (j = 0; j < count; j += 2)
					*(uint16_t *)&data[j] = ntohs(*(uint16_t *)&data[j]);
			} else if (format == 32) {
				for (j = 0; j < count; j += 2)
					*(uint32_t *)&data[j] = ntohl(*(uint32_t *)&data[j]);
			} else if (format != 8 && format != 0) {
				liberror_save_backtrace(NULL);
				goto corrupt_reply;
			}
			o += sizeof(void *);
			i += count;
			break;

		case '*':
			alignment = 1;
			ALIGN(&o, void *);
			*(void **)&msg[o] = data = &inbuf[i];
			o += sizeof(void *);
			stack[si].fmt = fmt;
			stack[si].msg = msg;
			stack[si].ic = ic;
			stack[si].oc = oc + 1;
			stack[si].o = o;
			stack[si].count = count;
			si += 1;
			count = counts[oc++];
			o = 0;
			msg = data;
			if (!count)
				goto jump_to_end_of_repeat;
			break;

		case '&':
			size = calculate_struct_size(&fmt[1], &alignment);
			ALIGN_VAR(&size, alignment);
			alignment = size;
			data = NULL;
			if (counts[oc]) {
				size *= counts[oc];
				if (size > ctx->aux_buf_size) {
					data = liberror_realloc(ctx->aux_buf, size);
					if (!data)
						return LIBAXL_ERROR_SYSTEM;
					ctx->aux_buf = data;
					ctx->aux_buf_size = size;
				} else {
					data = ctx->aux_buf;
				}
			}
			ALIGN(&o, void *);
			*(void **)&msg[o] = data;
			o += sizeof(void *);
			stack[si].fmt = fmt;
			stack[si].msg = msg;
			stack[si].ic = ic;
			stack[si].oc = oc + 1;
			stack[si].o = o;
			stack[si].count = count;
			si += 1;
			count = counts[oc++];
			o = 0;
			msg = data;
			if (!count)
				goto jump_to_end_of_repeat;
			break;

		case '/':
			if (--count) {
				fmt = stack[si - 1].fmt;
				ALIGN_VAR(&o, alignment);
			} else {
				if (0) {
				jump_to_end_of_repeat:
					for (j = 0;; fmt++) {
						if (*fmt == '*' || *fmt == '&') {
							j += 1;
						} else if (*fmt == '/') {
							if (!j--)
								break;
						} else if (!*fmt) {
							abort();
						}
					}
				}
				si -= 1;
				msg = stack[si].msg;
				ic = stack[si].ic;
				oc = stack[si].oc;
				o = stack[si].o;
				count = stack[si].count;
			}
			break;

		case '?':
			/* We know that code == LIBAXL_REQUEST_LIST_FONTS_WITH_INFO */
			if (!qc++) {
				if (!counts[0])
					goto done;
			} else {
				count = counts[0];
				counts[0] = counts[1];
				counts[1] = count;
			}
			break;

		default:
			abort();
		}
	}

	for (; *fmt && oc < ic && !counts[oc++]; fmt++) {
		if (*fmt == '*' || *fmt == '&') {
			ALIGN(&o, void *);
			*(void **)&msg[o] = NULL;
			o += sizeof(void *);
			for (j = 0;; fmt++) {
				if (*fmt == '*' || *fmt == '&') {
					j += 1;
				} else if (*fmt == '/') {
					if (!--j)
						break;
				} else if (!*fmt) {
					abort();
				}
			}
		} else if (*fmt == 'u' || *fmt == 'U' || *fmt == 'd') {
			ALIGN(&o, void *);
			*(void **)&msg[o] = NULL;
			o += sizeof(void *);
		} else {
			break;
		}
	}

	if (*fmt) {
		liberror_save_backtrace(NULL);
	short_msg:
		liberror_set_error("Received message's is shorter than expected", "libaxl_receive", "libaxl", LIBAXL_ERROR_SYSTEM);
		errno = EBADMSG;
		return LIBAXL_ERROR_SYSTEM;
	}

done:
	return 0;

corrupt_reply:
	liberror_set_error("Corrupt reply message received", "libaxl_receive", "libaxl", LIBAXL_ERROR_SYSTEM);
	errno = EBADMSG;
	return LIBAXL_ERROR_SYSTEM;
}
