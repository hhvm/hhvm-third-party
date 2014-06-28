/* 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef PTHREAD_TIMED_LOCK_SHIM
#define PTHREAD_TIMED_LOCK_SHIM

#define MUTEX_LOCK 1
#define WRITE_LOCK 2
#define READ_LOCK  3

inline int _pthread_try_lock(void* lock, timespec* timeout, int type) {
  switch (type) {
    case MUTEX_LOCK:
	  return pthread_mutex_trylock((pthread_mutex_t*)lock);
	case WRITE_LOCK:
	  return pthread_rwlock_trywrlock((pthread_rwlock_t*)lock);
	case READ_LOCK:
	  return pthread_rwlock_tryrdlock((pthread_rwlock_t*)lock);
  }
  return 0;
}

int _pthread_timedlock(void* lock, timespec* timeout, int type) {
  timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 10000000;

  int ret;
  while ((ret = _pthread_try_lock(lock, timeout, type)) == EBUSY) {
    timeval now;
    gettimeofday(&now, NULL);
    if (now.tv_sec >= timeout->tv_sec &&
       (now.tv_usec * 1000) >= timeout->tv_nsec) {
      return ETIMEDOUT;
    }
    nanosleep(&ts, NULL);
  }
  return ret;
}

int pthread_mutex_timedlock(pthread_mutex_t* mutex, timespec* timeout) {
  return _pthread_timedlock(mutex, timeout, MUTEX_LOCK);
}

int pthread_rwlock_timedwrlock(pthread_rwlock_t* lock, timespec* timeout) {
  return _pthread_timedlock(lock, timeout, WRITE_LOCK);
}

int pthread_rwlock_timedrdlock(pthread_rwlock_t* lock, timespec* timeout) {
  return _pthread_timedlock(lock, timeout, READ_LOCK);
}

#endif
