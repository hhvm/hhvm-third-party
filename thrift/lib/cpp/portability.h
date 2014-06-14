#ifndef THRIFT_PORTABILITY_H
#define THRIFT_PORTABILITY_H

#ifndef __APPLE__
#include <time.h>
#else
#include <mach/clock.h>
#include <mach/mach.h>
#include <sys/time.h>
#endif

class Timer {
public:
  static void GetMonotonicTime(timespec &ts) {
    #ifndef __APPLE__
      gettime(CLOCK_MONOTONIC, &ts);
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
