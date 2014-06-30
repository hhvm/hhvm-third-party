#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <winsock.h>    // timeval is defined in here.

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  timezone tz;

int gettimeofday(struct timeval * tp, struct timezone * tzp);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TIME_H */