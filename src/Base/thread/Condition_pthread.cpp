// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef WIN32

#include "base/thread/Condition.h"

#include <assert.h>
#include <pthread.h>
#include <time.h>

#include "base/thread/Mutex.h"

// Compile time assertion.
typedef int type_assertion[sizeof(void *) == sizeof(pthread_cond_t *) ? 1 : -1];

#define handle reinterpret_cast<pthread_cond_t *>(condition_)

Condition::Condition() : condition_(new pthread_cond_t) {
  pthread_cond_init(handle, NULL);
}

Condition::~Condition() {
  pthread_cond_destroy(handle);
  delete handle;
}

void Condition::Wake() {
  pthread_cond_signal(handle);
}

void Condition::Wait(Mutex *mutex) {
  assert(mutex);
  pthread_mutex_t *mutex_handle = reinterpret_cast<pthread_mutex_t *>(mutex->mutex_);
  pthread_cond_wait(handle, mutex_handle);
}

bool Condition::Wait(Mutex *mutex, size_t timeout) {
  if (timeout == 0) {
    Wait(mutex);
    return true;

  } else {
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_nsec += timeout % 1000 * 1000000;
    abstime.tv_sec += timeout / 1000 + abstime.tv_nsec / 1000000000;
    abstime.tv_nsec %= 1000000000;

    pthread_mutex_t *mutex_handle = reinterpret_cast<pthread_mutex_t *>(mutex->mutex_);
    return pthread_cond_timedwait(handle, mutex_handle, &abstime) == 0;
  }
}

#endif // WIN32
