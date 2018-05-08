// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef BASE_THREAD_MUTEXLOCKER_H__
#define BASE_THREAD_MUTEXLOCKER_H__

#include "base/thread/Mutex.h"

class MutexLocker {
 public:
  MutexLocker(Mutex *mutex) : mutex_(mutex), locked_(false) {
    Relock();
  }

  ~MutexLocker() {
    Unlock();
  }

  Mutex *mutex() const {
    return mutex_;
  }

  void Relock() {
    if (mutex_ && !locked_) {
      mutex_->Lock();
      locked_ = true;
    }
  }

  void Unlock() {
    if (mutex_ && locked_) {
      mutex_->Unlock();
      locked_ = false;
    }
  }

 private:
  explicit MutexLocker(const MutexLocker &);
  MutexLocker &operator = (const MutexLocker &);

  Mutex *mutex_;
  bool locked_;

};

#endif // BASE_THREAD_MUTEXLOCKER_H__
