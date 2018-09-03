// Copyright 2009 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef WIN32

#include "base/thread/Delay.h"

#include <time.h>

namespace base {

void Delay(size_t time) {
  struct timespec nanotime;
  nanotime.tv_nsec = time % 1000 * 1000000;
  nanotime.tv_sec = time / 1000;
  nanosleep(&nanotime, NULL);
}

} // namespace base

#endif // WIN32
