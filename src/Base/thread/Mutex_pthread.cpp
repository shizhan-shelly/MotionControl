// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef BASE_THREAD_MUTEX_PTHREAD_H__
#define BASE_THREAD_MUTEX_PTHREAD_H__

#ifndef WIN32

#include "base/thread/Mutex.h"

#include <pthread.h>

// Compile time assertion.
typedef int type_assertion[sizeof(void *) == sizeof(pthread_mutex_t *) ? 1 : -1];

#define handle reinterpret_cast<pthread_mutex_t *>(mutex_)

Mutex::Mutex() : mutex_(new pthread_mutex_t) {
  pthread_mutex_init(handle, NULL);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(handle);
  delete handle;
}

void Mutex::Lock() {
  pthread_mutex_lock(handle);
}

void Mutex::Unlock() {
  pthread_mutex_unlock(handle);
}

bool Mutex::TryLock() {
  return (pthread_mutex_trylock(handle) == 0);
}

#endif // WIN32

#endif // BASE_THREAD_MUTEX_PTHREAD_H__
