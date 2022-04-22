/* See LICENSE file for copyright and license details. */
#include "common.h"

static int
connect_tcp_ip(const char *host, int display)
{
	uint16_t port = libaxl_get_tcp_port(display);
	int fd;

	abort(); /* XXX */

	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &(int){1}, sizeof(int));
	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &(int){1}, sizeof(int));

	return -1;
}

static int
connect_unix(const char *path)
{
	struct sockaddr_un addr;
	int fd;

	fd = socket(PF_LOCAL, SOCK_STREAM | SOCK_CLOEXEC, 0);
	if (fd < 0) {
		liberror_save_backtrace(NULL);
		liberror_set_error_errno(strerror(errno), "socket", errno);
		return -1;
	}

	if (strlen(path) >= sizeof(addr.sun_path)) {
		liberror_save_backtrace(NULL);
		/* We could fix this with an O_PATH fd to the file,
		 * but we will not as other libraries probably do
		 * not do that, and there is something very wrong
		 * with your setup if the name is too long for
		 * `struct sockaddr_un`. */
		close(fd);
		errno = ENAMETOOLONG;
		liberror_set_error_errno("Path to X display socket is too long", "libaxl_connect_without_handshake", ENAMETOOLONG);
		return -1;
	}

	addr.sun_family = AF_LOCAL;
	stpcpy(addr.sun_path, path);
	if (connect(fd, (void *)&addr, (socklen_t)sizeof(addr))) {
		liberror_save_backtrace(NULL);
		liberror_set_error_errno(strerror(errno), "connect", errno);
		return -1;
	}

	return fd;
}

static int
connect_unix_abstract(const char *path, size_t len)
{
	struct sockaddr_un addr;
	int fd;

	fd = socket(PF_LOCAL, SOCK_STREAM | SOCK_CLOEXEC, 0);
	if (fd < 0) {
		liberror_save_backtrace(NULL);
		liberror_set_error_errno(strerror(errno), "socket", errno);
		return -1;
	}

	addr.sun_family = AF_LOCAL;
	memcpy(addr.sun_path, path, len);
	if (connect(fd, (void *)&addr, (socklen_t)len)) {
		liberror_save_backtrace(NULL);
		liberror_set_error_errno(strerror(errno), "connect", errno);
		return -1;
	}

	return fd;
}

LIBAXL_CONNECTION *
libaxl_connect_without_handshake(const char *host, const char *protocol, int display, int screen)
{
	LIBAXL_CONNECTION *conn;
	char path[sizeof("@/tmp/.X11-unix/X-") + 3 * sizeof(int)];
	int fd, len;

	if ((!protocol || !*protocol) && (!host || !*host)) {
		len = sprintf(path, "%c/tmp/.X11-unix/X%i", 0, display);
		fd = connect_unix(&path[1]);
		if (fd < 0) {
			fd = connect_unix_abstract(path, (size_t)len);
			if (fd >= 0) {
				liberror_pop_error();
			} else {
				fd = connect_tcp_ip("localhost", display);
				if (fd >= 0) {
					liberror_pop_error();
					liberror_pop_error();
				}
			}
		}

	} else if (!protocol || !*protocol ||
	           !strcasecmp(protocol, "tcp") || !strcasecmp(protocol, "inet") ||
	           !strcasecmp(protocol, "tcp6") || !strcasecmp(protocol, "inet6")) {
		fd = connect_tcp_ip(host, display);

	} else if (!strcmp(protocol, "unix")) {
		fd = connect_unix(host);

	} else {
		liberror_save_backtrace(NULL);
		liberror_set_error("Display server uses unsupported underlaying protocol",
		                   "libaxl_connect_without_handshake", "libaxl", LIBAXL_ERROR_PROTOCOL_NOT_SUPPORTED);
		return NULL;
	}

	if (fd < 0)
		return NULL;

	conn = libaxl_create(fd);
	if (conn)
		conn->info.default_screen_number = screen < 0 ? 0 : screen;

	return conn;
}
