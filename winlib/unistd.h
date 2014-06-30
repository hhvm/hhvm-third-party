/**
 * Posix api wrappers for windows
 */
#ifndef _UNISTD_H
#define _UNISTD_H

#include <io.h>
#include <process.h>
#include <sys/types.h>
#include <minwin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SSIZE_T ssize_t;

/* These are also defined in stdio.h. */
#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

/* These are also defined in stdio.h. */
#ifndef STDIN_FILENO
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* _commit is a CRT wrapper around FlushFileBuffers that manages errors and validation
   there is no separation of apis between flush data
   and flush metadata with NTFS so fsync and fdatasync are identical */
#define fsync _commit
#define fdatasync _commit
/* might need to change this to use _chsize_s for int64 size */
#define ftruncate _chsize
#define pipe(fds) _pipe(fds,4096, _O_BINARY) 

#define sleep(t) SleepEx(t*1000, 1)

#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_NB 4
#define LOCK_UN 8

typedef unsigned int mode_t;

#endif

/* sysconf for windows */
#define _SC_PAGESIZE         1
#define _SC_NPROCESSORS_CONF 2
#define _SC_NPROCESSORS_ONLN 3
#define _SC_PHYS_PAGES       4

long sysconf(int name);

/* posix wrappers - in unistd.c */

int flock(int fd, int op);
int usleep(unsigned int useconds);
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
int truncate(const char *path, off_t length);

#ifdef __cplusplus
}
#endif

#endif /* _UNISTD_H */