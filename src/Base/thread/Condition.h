// Copyright 2009 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef BASE_THREAD_CONDITION_H__
#define BASE_THREAD_CONDITION_H__

#include <sys/types.h>

class Mutex;

/**
 * Condition is an exclusive lock to signal synchronization events.
 *
 * Non recursive.
 *
 */
class Condition {
 public:
  Condition();
  ~Condition();

  void Wake();
  bool Wait(Mutex *mutex);
  bool Wait(Mutex *mutex, size_t timeout); // Milliseconds, 0 for infinite.

 private:
  explicit Condition(const Condition &);
  Condition &operator = (const Condition &);

  void *condition_;

};

#endif // BASE_THREAD_CONDITION_H__
