#ifndef _SYS_UIO_H
#define _SYS_UIO_H

#include <inttypes.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

struct iovec
{
	void	*iov_base; /* Base address of a memory region for input or output */
	size_t	iov_len; /* The size of the memory pointed to by iov_base */
};

// ReadFileScatter, WriteFileGather, WSASend, and WSARecv.
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_UIO_H */