/* See LICENSE file for copyright and license details. */
#include "common.h"

enum {
      FamilyInternet  = 0,
      FamilyDECnet    = 1,
      FamilyChaos     = 2,
      FamilyInternet6 = 6,
      FamilyLocal     = 256
};

static char *
path_in_home(const char *filename)
{
	const char *home;
	struct passwd *pwd, pwd_buf;
	size_t buf_size;
	char *buf, *ret;
	int r;

	home = getenv("HOME");
	if (!home || !*home) {
		buf_size = sysconf(_SC_GETPW_R_SIZE_MAX);
		buf_size = buf_size == -1 ? 16384 : buf_size;
		buf = alloca(buf_size);
		r = getpwuid_r(getuid(), &pwd_buf, buf, buf_size, &pwd);
		if (!pwd) {
			liberror_save_backtrace(NULL);
			r = (r == ENOENT || r == ESRCH || r == EBADF || r == EPERM || r == EIO /* glibc bug */) ? 0 : r;
			if (r) {
				liberror_set_error_errno(strerror(r), "getpwuid_r", r);
			} else {
				liberror_set_error_errno("User does not exist", "getpwuid_r", "libaxl",
				                         LIBAXL_ERROR_USER_DOES_NOT_EXIST);
			}
			return NULL;
		} else {
			home = pwd->pw_dir;
			if (!home || !*home) {
				liberror_save_backtrace(NULL);
				liberror_set_error_errno("User does not have a home", "libaxl_connect", "libaxl",
				                         LIBAXL_ERROR_USER_DOES_NOT_HAVE_A_HOME);
				return NULL;
			}
		}
	}

	ret = liberror_malloc(strlen(home) + strlen(filename) + 2);
	if (!ret)
		return NULL;

	stpcpy(stpcpy(stpcpy(ret, home), "/"), filename);

	return ret;
}

static char *
get_auth_file(int *freep)
{
	char *xauthfile = getenv("XAUTHORITY");
	if (!xauthfile || !*xauthfile) {
		xauthfile = path_in_home(".Xauthority");
		*freep = 1;
	} else {
		*freep = 0;
	}
	return xauthfile;
}

static int
next_auth(int authfd, char **authbufp, size_t *bufsizep, size_t *lenp, size_t *havep)
{
	ssize_t r;
	size_t got = *havep, need = 4;
	int stage;
	void *new;

	*lenp = 0;

	for (stage = 0; stage < 4; stage++) {
		while (got < need) {
			if (need > *bufsizep) {
				new = liberror_realloc(*authbufp, need);
				if (!new)
					return -1;
				*authbufp = new;
				*bufsizep = need;
			}
			r = read(authfd, &(*authbufp)[got], *bufsizep - got);
			if (r < 0) {
				liberror_save_backtrace(NULL);
				liberror_set_error_errno(strerror(errno), "read", errno);
				return -1;
			} else if (!r) {
				return 0;
			}
			got += (size_t)r;
		}
		need += (size_t)ntohs(*(uint16_t *)&(*authbufp)[need - 2]) + (stage < 3 ? 2 : 0);
	}

	*lenp = need;
	if (*havep > need)
		*havep -= need;
	else
		*havep = got - need;

	return 0;
}

static int
get_auth(const char *xauthfile, int sockfd, const char *host, const char *protocol, int display,
         char **authnamep, size_t *authnamelenp, char **authdatap, size_t *authdatalenp, char **authbufp)
{
	int authfd, family, saved_errno;
	char hostname[HOST_NAME_MAX + 1], number[2 + 3 * sizeof(int)];
	struct sockaddr_storage sockaddr;
	socklen_t sockaddrlen = (socklen_t)sizeof(sockaddr);
	size_t bufsize = 128, len, have = 0, off, numberlen, hostnamelen;
	uint16_t partlen;

	(void) host;
	(void) protocol;

	*authnamep = *authdatap = *authbufp = NULL;
	*authnamelenp = *authdatalenp = 0;

	numberlen = (size_t)sprintf(number, "%i", display);

	if (gethostname(hostname, HOST_NAME_MAX))
		stpcpy(hostname, "localhost");
	hostnamelen = strlen(hostname);

	if (getpeername(sockfd, (void *)&sockaddr, &sockaddrlen)) {
		liberror_save_backtrace(NULL);
		liberror_set_error_errno(strerror(errno), "getsockname", errno);
		return -1;
	}

	switch (sockaddr.ss_family) {
	case AF_LOCAL:
		family = FamilyLocal;
		break;
	case AF_INET:
		family = FamilyInternet; /* XXX */
		return 0;
	case AF_INET6:
		family = FamilyInternet6; /* XXX */
		return 0;
	default:
		return 0;
	}

	*authbufp = liberror_malloc(bufsize);
	if (!*authbufp)
		return -1;

	authfd = open(xauthfile, O_RDONLY);
	if (authfd < 0 && errno != ENOENT) {
		liberror_save_backtrace(NULL);
		liberror_set_error_errno(strerror(errno), "open", errno);
		return -1;
	} else if (authfd < 0) {
		return 0;
	}

	for (;; memmove(*authbufp, &(*authbufp)[len], have)) {
		if (next_auth(authfd, authbufp, &bufsize, &len, &have)) {
			liberror_save_backtrace(NULL);
			liberror_set_error_errno(strerror(errno), "read", errno);
			saved_errno = errno;
			close(authfd);
			errno = saved_errno;
			return -1;
		} else if (!len) {
			break;
		}

		if (*(uint16_t *)&(*authbufp)[0] != htons(family))
			continue;
		if (*(uint16_t *)&(*authbufp)[2] != htons((uint16_t)hostnamelen))
			continue;
		if (memcmp(&(*authbufp)[4], hostname, hostnamelen))
			continue;
		off = 4 + (size_t)hostnamelen;
		partlen = ntohs(*(uint16_t *)&(*authbufp)[off]);
		off += 2;
		if (partlen != numberlen)
			continue;
		if (memcmp(&(*authbufp)[off], number, numberlen))
			continue;
		off += numberlen;

		*authnamelenp = (size_t)ntohs(*(uint16_t *)&(*authbufp)[off]);
		off += 2;
		*authnamep = &(*authbufp)[off];
		off += *authnamelenp;
		*authdatalenp = (size_t)ntohs(*(uint16_t *)&(*authbufp)[off]);
		off += 2;
		*authdatap = &(*authbufp)[off];

		break;
	}

	close(authfd);
	return 0;
}

LIBAXL_CONNECTION *
libaxl_connect(const char *restrict display, char **restrict reasonp)
{
	struct liberror_state error_state;
	LIBAXL_CONNECTION *conn = NULL;
	LIBAXL_CONTEXT *ctx = NULL;
	int xauthfile_free = 0, dispnum, screen, major, minor, r;
	char *xauthfile = NULL, *host = NULL, *protocol = NULL;
	char *authname = NULL, *authdata = NULL, *authbuf = NULL;
	size_t authnamelen, authdatalen;
	int saved_errno = errno;

	if (reasonp)
		*reasonp = NULL;

	r = libaxl_parse_display(display, &host, &protocol, &dispnum, &screen);
	if (r)
		goto fail;

	xauthfile = get_auth_file(&xauthfile_free);
	if (!xauthfile)
		goto fail;

	conn = libaxl_connect_without_handshake(host, protocol, dispnum, screen);
	if (!conn)
		goto fail;

	ctx = libaxl_context_create(conn);
	if (!ctx)
		goto fail;

	if (get_auth(xauthfile, conn->fd, host, protocol, dispnum, &authname, &authnamelen, &authdata, &authdatalen, &authbuf))
		goto fail;

	r = libaxl_send_handshake(ctx, authname, authnamelen, authdata, authdatalen, MSG_NOSIGNAL);
	if (r) {
		if (r == LIBAXL_ERROR_SYSTEM && errno == EINPROGRESS) {
			for (;;) {
				r = libaxl_flush(conn, MSG_NOSIGNAL);
				if (r != LIBAXL_ERROR_SYSTEM || errno != EINPROGRESS)
					break;
				liberror_pop_error();
			}
		}
		if (r)
			goto fail;
		liberror_pop_error();
	}

	errno = saved_errno;

	r = libaxl_receive_handshake(ctx, &major, &minor, reasonp, MSG_NOSIGNAL);
	switch (r) {
	case LIBAXL_HANDSHAKE_FAILED: /* XXX */
	case LIBAXL_HANDSHAKE_AUTHENTICATE: /* XXX */
		abort();
		break;

	case LIBAXL_HANDSHAKE_SUCCESS:
		break;

	default:
		goto fail;
	}

	if (xauthfile_free)
		free(xauthfile);
	libaxl_context_free(ctx);
	free(authbuf);
	free(host);
	free(protocol);
	return conn;

fail:
	liberror_start(&error_state);
	if (xauthfile_free)
		free(xauthfile);
	free(authbuf);
	free(host);
	free(protocol);
	libaxl_context_free(ctx);
	libaxl_close(conn);
	liberror_end(&error_state);
	return NULL;
}
