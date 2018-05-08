// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

/*
 * Mutex is an exclusive lock to protect critical sections, mutex holder has
 * unlimited access while all other accessors blocked until mutex is unlocked.
 *
 * Non recursive.
 *
 */

#ifndef BASE_THREAD_MUTEX_H__
#define BASE_THREAD_MUTEX_H__

namespace internal {
class MutexContext;
} // internal

class Mutex {
 public:
  friend class Condition;

  Mutex();
  ~Mutex();

  void Lock();
  void Unlock();
  bool TryLock();

 private:
  explicit Mutex(const Mutex &);
  Mutex &operator = (const Mutex &);

  void *mutex_;

};

#endif // BASE_THREAD_MUTEX_H__
