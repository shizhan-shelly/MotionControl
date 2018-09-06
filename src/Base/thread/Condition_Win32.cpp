// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifdef WIN32

#include "base/thread/Condition.h"

#include <assert.h>
#include <Windows.h>

#include "base/thread/Mutex.h"

//Compile time assertion.
typedef int type_assertion[sizeof(void *) == sizeof(HANDLE) ? 1 : -1];

#define handle reinterpret_cast<HANDLE>(condition_)

Condition::Condition() {
  condition_ = reinterpret_cast<void *>(CreateEventW(NULL, FALSE, FALSE, NULL));
}

Condition::~Condition() {
  CloseHandle(handle);
}

void Condition::Wake() {
  SetEvent(handle);
}

void Condition::Wait(Mutex *mutex) {
  Wait(mutex, 0);
}

bool Condition::Wait(Mutex *mutex, size_t timeout) {
  assert(mutex);

  ResetEvent(handle);

  DWORD time = INFINITE;
  if (timeout != 0) {
    time = static_cast<DWORD>(timeout);
  }

  HANDLE mutex_handle = reinterpret_cast<HANDLE>(mutex->mutex_);
  DWORD ret = SignalObjectAndWait(mutex_handle, handle, time, FALSE);
  if (ret != WAIT_TIMEOUT && ret != WAIT_OBJECT_0) {
    assert(false);
  }

  if (WaitForSingleObject(mutex_handle, INFINITE) != WAIT_OBJECT_0) {
    assert(false);
  }

  return ret == WAIT_OBJECT_0;
}

#endif // WIN32
