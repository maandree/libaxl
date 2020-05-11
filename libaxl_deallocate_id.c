/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_deallocate_id(LIBAXL_CONTEXT *ctx, libaxl_id_t id)
{
	LIBAXL_CONNECTION *conn = ctx->conn;
	struct id_pool *pool = NULL, *node;
	uint32_t inc = (uint32_t)1 << conn->xid_shift;
	int ret = 0;

	pool = atomic_exchange(&conn->xid_pool, pool);
	if (pool) {
		for (node = pool;; node = node->next) {
			if (id + inc == node->first) {
				node->first = id;
				goto out;
			} else if (node->last + inc == id) {
				node->last = id;
				goto out;
			}
			if (!node->next)
				break;
		}
		node->next = liberror_malloc(sizeof(*node->next));
		if (node->next) {
			node->next->first = id;
			node->next->last = id;
			atomic_init(&node->next->next, NULL);
		} else {
			ret = -1;
		}
	} else {
		pool = liberror_malloc(sizeof(*pool));
		if (pool) {
			pool->first = id;
			pool->last = id;
			atomic_init(&pool->next, NULL);
		} else {
			ret = -1;
		}
	}

out:
	while ((pool = atomic_exchange(&conn->xid_pool, pool))) {
		for (node = pool; node->next; node = node->next);
		node->next = atomic_exchange(&conn->xid_pool, NULL);
	}

	return ret;
}

