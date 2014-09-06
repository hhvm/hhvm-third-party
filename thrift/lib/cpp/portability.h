#ifndef THRIFT_PORTABILITY_H
#define THRIFT_PORTABILITY_H

#ifndef __APPLE__
# include <time.h>
# if !defined(__APPLE__) && !defined(__FreeBSD__) && \
     !defined(__OpenBSD__) && !defined(__NetBSD__)
#  include <features.h>
# endif
#else
# include <mach/clock.h>
# include <mach/mach.h>
# include <sys/time.h>
#endif

#ifndef __GLIBC_PREREQ
  #define __GLIBC_PREREQ(maj, min) \
    ((__GLIBC__ << 16) + __GLIBC_MINOR__ >= ((maj) << 16) + (min))
#endif

#ifndef __GNUC_PREREQ
  #define __GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#endif

# if defined(__APPLE__) || defined(__FreeBSD__) || \
     defined(__OpenBSD__) || defined(__NetBSD__)
# ifndef s6_addr16
#  define s6_addr16 __u6_addr.__u6_addr16
# endif
# ifndef s6_addr32
#  define s6_addr32 __u6_addr.__u6_addr32
# endif
#endif

class Timer {
public:
  static void GetMonotonicTime(timespec &ts) {
    #ifndef __APPLE__
      clock_gettime(CLOCK_MONOTONIC, &ts);
    #else
      struct timeval tv;
      gettimeofday(&tv, nullptr);
      TIMEVAL_TO_TIMESPEC(&tv, &ts);
    #endif
  }

  static void GetRealtimeTime(timespec &ts) {
    #ifndef __APPLE__
      clock_gettime(CLOCK_REALTIME, &ts);
    #else
      clock_serv_t cclock;
      mach_timespec_t mts;
      host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
      clock_get_time(cclock, &mts);
      mach_port_deallocate(mach_task_self(), cclock);
      ts.tv_sec = mts.tv_sec;
      ts.tv_nsec = mts.tv_nsec;
    #endif
  }
};

#endif // THRIFT_PORTABILITY_H
