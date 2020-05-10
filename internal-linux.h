/* See LICENSE file for copyright and license details. */

#include <linux/futex.h>
#include <sys/syscall.h>

#include "internal-llmutex.h"


typedef volatile _Atomic uint32_t MUTEX;
_Static_assert(sizeof(MUTEX) == sizeof(uint32_t));


#define INIT_MUTEX(MUTEX)\
	((void)0) /* TODO atomic_init(&(MUTEX), 0) */

#define _TRYLOCK(MUTEX)\
	!atomic_exchange(&(MUTEX), 1)

#define _LOCK(MUTEX)\
	do {\
		while (!_TRYLOCK(MUTEX))\
			_WAIT(MUTEX);\
	} while (0)

#define _UNLOCK(MUTEX)\
	do {\
		atomic_store(&(MUTEX), 0);\
		if (syscall(SYS_futex, &(MUTEX), FUTEX_PRIVATE_FLAG | FUTEX_WAKE, INT_MAX, NULL, 0, 0) < 0) {\
			/* TODO handle of error in _UNLOCK */\
		}\
	} while (0)

#define _WAIT(MUTEX)\
	do {\
		if (syscall(SYS_futex, &(MUTEX), FUTEX_PRIVATE_FLAG | FUTEX_WAIT, 1, NULL, 0, 0) < 0) {\
			/* TODO handle of error in _WAIT */\
		}\
	} while (0)
