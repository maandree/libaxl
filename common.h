/* See LICENSE file for copyright and license details. */
#include "libaxl.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(__linux__)
# include "internal-linux.h"
#endif

#if !defined(NO_LIBERROR)
# include <liberror.h>
#else
# define liberror_save_backtrace(...)  ((void) 0)
# define liberror_set_error(...)       ((void) 0)
# define liberror_set_error_errno(...) ((void) 0)
# define liberror_reset_error()        ((void) 0)
#endif

#if !defined(NO_LIBERROR) && !defined(NO_LIBERROR_LIBC)
# include <liberror-libc.h>
#else
# if defined(NO_LIBERROR)
#  define __checked_ptr(X, _FUN)     X
#  define __checked_ssize_t(X, _FUN) X
# else
#  define DEFINE_CHECKED(TYPE, NAME)\
	static inline TYPE\
	NAME(TYPE ret, const char *func)\
	{\
		if (!ret)\
			liberror_set_error_errno(strerror(errno), func, errno);\
		return ret;\
	}
DEFINE_CHECKED(void *, __checked_ptr)
DEFINE_CHECKED(ssize_t, __checked_ssize_t)
# endif
# define liberror_malloc(N)               __checked_ptr(malloc(N), "malloc")
# define liberror_realloc(P, N)           __checked_ptr(realloc(P, N), "realloc")
# define liberror_send(FD, B, N, F, _NAM) __checked_ssize_t(send(FD, B, N, F), "send")
# define liberror_recv(FD, B, N, F, _NAM) __checked_ssize_t(recv(FD, B, N, F), "recv")
# define liberror_send_failed(FD, B, N, F, _NAM) ((void) 0)
# define liberror_recv_failed(FD, B, N, F, _NAM) ((void) 0)
#endif

#define X_TCP_PORT 6000

struct libaxl_connection {
	int                fd;
	uint16_t           last_seqnum;
	LIBAXL_CONNECTION_RWLOCK; /* INIT_LIBAXL_CONNECTION_RWLOCK(&.) */
	LIBAXL_CONTEXT    *pending_out;
	size_t             in_progress;
	size_t             in_buf_size;
	char              *in_buf;
	uint32_t           xid_base; /* TODO information for these are send by server when connecting { */
	uint32_t           xid_bits;
	uint32_t           xid_shift; /* } */
	uint8_t            request_map[1UL << 16];
};

struct libaxl_context {
	LIBAXL_CONNECTION *conn;
	size_t             refcount;
	LIBAXL_CONTEXT    *next_pending_out;
	size_t             out_length;
	size_t             out_progress;
	size_t             out_buf_size;
	char              *out_buf;
	size_t             in_buf_size;
	char              *in_buf;
};

#define ALIGN(VP, T)\
	do {\
		if (*(VP) & (_Alignof(T) - 1)) {\
			*(VP) |= _Alignof(T) - 1;\
			*(VP) += 1;\
		}\
	} while (0)

#if INT_MIN + 1 == -INT_MAX
# define TWOS_COMPLEMENT8(VP)  ((void)0)
# define TWOS_COMPLEMENT16(VP) ((void)0)
# define TWOS_COMPLEMENT32(VP) ((void)0)
#else
# define TWOS_COMPLEMENT8(VP)\
	do {\
		if (*(int8_t *)(VP) < 0)\
			*(uint8_t *)(VP) = (uint16_t)~(uint16_t)(-*(int16_t *)(VP) - 1)\
	} while (0)
# define TWOS_COMPLEMENT16(VP)\
	do {\
		if (*(int16_t *)(VP) < 0)\
			*(uint16_t *)(VP) = (uint16_t)~(uint16_t)(-*(int16_t *)(VP) - 1)\
	} while (0)
# define TWOS_COMPLEMENT32(VP)\
	do {\
		if (*(int32_t *)(VP) < 0)\
			*(uint32_t *)(VP) = (uint32_t)~(uint32_t)(-*(int32_t *)(VP) - 1)\
	} while (0)
#endif

#if INT_MIN + 1 == -INT_MAX
# define UNTWOS_COMPLEMENT8(VP)  ((void)0)
# define UNTWOS_COMPLEMENT16(VP) ((void)0)
# define UNTWOS_COMPLEMENT32(VP) ((void)0)
#else
# define UNTWOS_COMPLEMENT8(VP)\
	do {\
		if (*(uint8_t *)(VP) & ((uint8_t)1 << 7))\
			*(int8_t *)(VP) = -(int8_t)(~*(uint8_t *)(VP) + (uint8_t)1);\
	} while (0)
# define UNTWOS_COMPLEMENT16(VP)\
	do {\
		if (*(uint16_t *)(VP) & ((uint16_t)1 << 15))\
			*(int16_t *)(VP) = -(int16_t)(~*(uint16_t *)(VP) + (uint16_t)1);\
	} while (0)
# define UNTWOS_COMPLEMENT32(VP)\
	do {\
		if (*(uint32_t *)(VP) & ((uint32_t)1 << 31))\
			*(int32_t *)(VP) = -(int32_t)(~*(uint32_t *)(VP) + (uint32_t)1);\
	} while (0)
#endif