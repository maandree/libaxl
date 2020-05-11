/* See LICENSE file for copyright and license details. */
#include "common.h"

libaxl_id_t
libaxl_generate_id(LIBAXL_CONTEXT *ctx)
{
	LIBAXL_CONNECTION *conn = ctx->conn;
	struct id_pool *pool = NULL, *next, *last;
	uint32_t id;

	pool = atomic_exchange(&conn->xid_pool, pool);
	if (pool) {
		id = pool->first;
		pool->first += (uint32_t)1 << conn->xid_shift;
		if (id == pool->last) {
			next = pool->next;
			if (next) {
				free(pool);
				pool = next;
			}
			next = NULL;
			if (atomic_compare_exchange_strong(&conn->xid_pool, &next, pool))
				return id;
			if (!pool->next) {
				free(pool);
				return id;
			}
		}
		while ((pool = atomic_exchange(&conn->xid_pool, pool))) {
			for (last = pool; last->next; last = last->next);
			last->next = atomic_exchange(&conn->xid_pool, NULL);
		}
		return id;
	}

	id = atomic_fetch_add(&conn->xid_last, 1);
	if (id <= conn->xid_max)
		return (id << conn->xid_shift) | conn->xid_base;

	atomic_fetch_sub(&conn->xid_last, 1);

	liberror_save_backtrace(NULL);
	liberror_set_error("Request has been buffered and is ready to be sent",
	                   "libaxl_generate_id", "libaxl", LIBAXL_ERROR_OUT_OF_RESOURCE_IDS);
	return 0;
}
