// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifdef WIN32

#include "base/thread/Mutex.h"

#include <windows.h>

// Compile time assertion.
typedef int type_assertion[sizeof(void *) == sizeof(HANDLE) ? 1 : -1];

#define handle reinterpret_cast<HANDLE>(mutex_)

/*
 * We use Event here since critical section and mutex are recursive locks.
 */
Mutex::Mutex() {
  mutex_ = reinterpret_cast<void *>(CreateEvent(NULL, FALSE, TRUE, NULL));
}

Mutex::~Mutex() {
  CloseHandle(handle);
}

void Mutex::Lock() {
  WaitForSingleObject(handle, INFINITE);
}

void Mutex::Unlock() {
  SetEvent(handle);
}

bool Mutex::TryLock() {
  bool result = false;
  if (WaitForSingleObject(handle, 0) == WAIT_OBJECT_0) {
    result = true;
  }
  return result;
}

#endif // WIN32
