/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_get_decnet_object(char *buf, size_t size, int display)
{
	return liberror_snprintf(buf, size, "X$X%i", display);
}
