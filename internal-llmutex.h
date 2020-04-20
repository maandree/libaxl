/* See LICENSE file for copyright and license details. */

#define LIBAXL_CONNECTION_RWLOCK\
	volatile _Atomic char nrguard_send;\
	volatile _Atomic char nrguard_recv;\
	MUTEX                 exguard_send;\
	MUTEX                 exguard_recv;\
	MUTEX                 exwait_send;\
	MUTEX                 exwait_recv;\
	volatile size_t       nreaders_send;\
	volatile size_t       nreaders_recv

#define INIT_LIBAXL_CONNECTION_RWLOCK(CONN)\
	do {\
		atomic_init(&(CONN)->nrguard_send, 0);\
		atomic_init(&(CONN)->nrguard_recv, 0);\
		INIT_MUTEX((CONN)->exguard_send);\
		INIT_MUTEX((CONN)->exguard_recv);\
		INIT_MUTEX((CONN)->exwait_send);\
		INIT_MUTEX((CONN)->exwait_recv);\
		(CONN)->nreaders_send = 0;\
		(CONN)->nreaders_recv = 0;\
	} while (0)

#define    WLOCK_CONNECTION_(CONN, SUFFIX)    _LOCK((CONN)->exguard_##SUFFIX)
#define WTRYLOCK_CONNECTION_(CONN, SUFFIX) _TRYLOCK((CONN)->exguard_##SUFFIX)
#define  WUNLOCK_CONNECTION_(CONN, SUFFIX)  _UNLOCK((CONN)->exguard_##SUFFIX)

#define   RLOCK_CONNECTION_(CONN, SUFFIX)\
	do {\
		char old_val__;\
		do {\
			do {\
				old_val__ = atomic_fetch_or(&(CONN)->nrguard_##SUFFIX, 1);\
			} while (old_val__ == 1);\
			if (old_val__ == 0) {\
				if (!(CONN)->nreaders_##SUFFIX++) {\
					if (WTRYLOCK_CONNECTION_(CONN, SUFFIX)) {\
						atomic_store(&(CONN)->nrguard_##SUFFIX, 2);\
					} else {\
						_LOCK((CONN)->exwait_##SUFFIX);\
						atomic_store(&(CONN)->nrguard_##SUFFIX, 2);\
						WLOCK_CONNECTION_(CONN, SUFFIX);\
						_UNLOCK((CONN)->exwait_##SUFFIX);\
					}\
				}\
				atomic_store(&(CONN)->nrguard_##SUFFIX, 0);\
				break;\
			} else {\
				_WAIT((CONN)->exwait_##SUFFIX);\
			}\
		} while (old_val__ == 2);\
	} while (0)

#define RUNLOCK_CONNECTION_(CONN, SUFFIX)\
	do {\
		char old_val__;\
		do {\
			old_val__ = atomic_fetch_or(&(CONN)->nrguard_##SUFFIX, 1);\
		} while (old_val__);\
		if (!--(CONN)->nreaders_##SUFFIX)\
			WUNLOCK_CONNECTION_((CONN), SUFFIX);\
		atomic_store(&(CONN)->nrguard_##SUFFIX, 0);\
	} while (0)

#define   WLOCK_CONNECTION_SEND(CONN)   WLOCK_CONNECTION_(CONN, send)
#define WUNLOCK_CONNECTION_SEND(CONN) WUNLOCK_CONNECTION_(CONN, send)
#define   RLOCK_CONNECTION_SEND(CONN)   RLOCK_CONNECTION_(CONN, send)
#define RUNLOCK_CONNECTION_SEND(CONN) RUNLOCK_CONNECTION_(CONN, send)

#define   WLOCK_CONNECTION_RECV(CONN)   WLOCK_CONNECTION_(CONN, recv)
#define WUNLOCK_CONNECTION_RECV(CONN) WUNLOCK_CONNECTION_(CONN, recv)
#define   RLOCK_CONNECTION_RECV(CONN)   RLOCK_CONNECTION_(CONN, recv)
#define RUNLOCK_CONNECTION_RECV(CONN) RUNLOCK_CONNECTION_(CONN, recv)
