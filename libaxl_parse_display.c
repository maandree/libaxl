/* See LICENSE file for copyright and license details. */
#include "common.h"

int
libaxl_parse_display(const char *name, char **hostp, char **protocolp, int *displayp, int *screenp)
{
	char *p;
	size_t n;
	unsigned long int ul;
	int err;
	int saved_errno = errno;
	struct stat st;

	*hostp     = NULL;
	*protocolp = NULL;
	*displayp  = 0;
	*screenp   = 0;

	/* Get display server name string, if not specified */
	if (!name || !*name) {
		name = getenv("DISPLAY");
		if (!name || !*name) {
			liberror_save_backtrace(NULL);
			liberror_set_error("No display server specified", "libaxl_parse_display", "libaxl",
			                   LIBAXL_ERROR_NO_DISPLAY_SERVER_SPECIFIED);
			err = LIBAXL_ERROR_NO_DISPLAY_SERVER_SPECIFIED;
			goto fail;
		}
	}

	/* Get path and test if protocol is "unix" */
	p = strrchr(name, '.');
	if (p && isdigit(*p)) {
		errno = 0;
		ul = strtoul(p, &p, 10);
		if (errno || ul > (unsigned long int)INT_MAX)
			p = NULL;
		else
			*screenp = (int)ul;
	}
	n = p ? (size_t)(p - name) : strlen(name);
	if (n) {
		*hostp = liberror_malloc(n + 1);
		if (!*hostp)
			goto errno_fail;
		memcpy(*hostp, name, n);
		(*hostp)[n] = '\0';
		if (stat(*hostp, &st) || (st.st_mode & S_IFMT) != S_IFSOCK) {
			free(*hostp);
			*hostp = NULL;
			goto normal;
		}
		*protocolp = liberror_malloc(sizeof("unix"));
		if (!*protocolp)
			goto errno_fail;
		stpcpy(*protocolp, "unix");
		goto done;
	}

normal:
	/* Get protocol */
	p = strrchr(name, '/');
	if (p) {
		n = (size_t)(p - name);
		*protocolp = liberror_malloc(n + 1);
		if (*protocolp)
			goto errno_fail;
		memcpy(*protocolp, name, n);
		(*protocolp)[n] = '\0';
		name = &p[1];
	}

	/* Get host */
	p = strrchr(name, ':');
	if (!p) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Invalid display name: no display index", "libaxl_parse_display", "libaxl",
		                   LIBAXL_ERROR_INVALID_DISPLAY_NAME_NO_DISPLAY_INDEX);
		err = LIBAXL_ERROR_INVALID_DISPLAY_NAME_NO_DISPLAY_INDEX;
		goto fail;
	} else {
		n = (size_t)(p - name);
		*hostp = liberror_malloc(n + 1);
		if (!*hostp)
			goto errno_fail;
		memcpy(*hostp, name, n);
		(*hostp)[n] = '\0';
		name = &p[1];
	}

	/* Get display */
	if (!isdigit(*name)) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Invalid display name: no display index", "libaxl_parse_display", "libaxl",
		                   LIBAXL_ERROR_INVALID_DISPLAY_NAME_NO_DISPLAY_INDEX);
		err = LIBAXL_ERROR_INVALID_DISPLAY_NAME_NO_DISPLAY_INDEX;
		goto fail;
	}
	saved_errno = errno;
	errno = 0;
	ul = strtoul(name, (void *)&name, 10);
	if (errno || ul > (unsigned long int)(*hostp ? 65535 - X_TCP_PORT : INT_MAX)) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Invalid display name: display index is out of domain", "libaxl_parse_display", "libaxl",
		                   LIBAXL_ERROR_INVALID_DISPLAY_NAME_DISPLAY_INDEX_OUT_OF_DOMAIN);
		err = LIBAXL_ERROR_INVALID_DISPLAY_NAME_DISPLAY_INDEX_OUT_OF_DOMAIN;
		goto fail;
	}
	*displayp = (int)ul;
	errno = saved_errno;

	/* Get screen */
	if (*name)
		goto done;
	if (!isdigit(*name)) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Invalid display name: invalid screen index", "libaxl_parse_display", "libaxl",
		                   LIBAXL_ERROR_INVALID_DISPLAY_NAME_INVALID_SCREEN_INDEX);
		err = LIBAXL_ERROR_INVALID_DISPLAY_NAME_INVALID_SCREEN_INDEX;
		goto fail;
	}
	errno = 0;
	ul = strtoul(name, (void *)&name, 10);
	if (errno || ul > (unsigned long int)INT_MAX) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Invalid display name: screen index is out of domain", "libaxl_parse_display", "libaxl",
		                   LIBAXL_ERROR_INVALID_DISPLAY_NAME_SCREEN_INDEX_OUT_OF_DOMAIN);
		err = LIBAXL_ERROR_INVALID_DISPLAY_NAME_SCREEN_INDEX_OUT_OF_DOMAIN;
		goto fail;
	}
	*screenp = (int)ul;
	if (*name) {
		liberror_save_backtrace(NULL);
		liberror_set_error("Invalid display name: invalid screen index", "libaxl_parse_display", "libaxl",
		                   LIBAXL_ERROR_INVALID_DISPLAY_NAME_INVALID_SCREEN_INDEX);
		err = LIBAXL_ERROR_INVALID_DISPLAY_NAME_INVALID_SCREEN_INDEX;
		goto fail;
	}

done:
	errno = saved_errno;
	return 0;

errno_fail:
	err = LIBAXL_ERROR_SYSTEM;
fail:
	free(*protocolp);
	*protocolp = NULL;
	free(*hostp);
	*hostp = NULL;
	if (err != LIBAXL_ERROR_SYSTEM)
		errno = EINVAL;
	return err;
}
