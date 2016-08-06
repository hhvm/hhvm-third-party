#include <minwin.h>
#include <sys/uio.h>

ssize_t readv(int fd, const struct iovec *iov, int iovcnt) {
	DWORD bytes_written = 0;
	return bytes_written;
}
ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
	DWORD bytes_written = 0;
	return bytes_written;
}