#ifndef _SYS_POLL_H
#define _SYS_POLL_H

#ifdef __cplusplus
extern "C" {
#endif

#define POLLIN      0x0001      /* any readable data available   */
#define POLLPRI     0x0002      /* OOB/Urgent readable data      */
#define POLLOUT     0x0004      /* file descriptor is writeable  */
#define POLLERR     0x0008      /* some poll error occurred      */
#define POLLHUP     0x0010      /* file descriptor was "hung up" */
#define POLLNVAL    0x0020      /* requested events "invalid"    */
#define POLLRDNORM  0x0040
#define POLLRDBAND  0x0080
#define POLLWRNORM  0x0100
#define POLLWRBAND  0x0200

struct pollfd
{
	int fd;                       /* which file descriptor to poll */
	short events;                 /* events we are interested in   */
	short revents;                /* events found on return        */
};

typedef unsigned long nfds_t;

extern int poll(struct pollfd *pfd, nfds_t nfd, int timeout);

#ifdef __cplusplus
}
#endif


#endif /* _SYS_POLL_H */