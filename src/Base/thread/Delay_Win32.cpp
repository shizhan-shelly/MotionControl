// Copyright 2009 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifdef WIN32

#include "base/thread/Delay.h"

#include <Windows.h>

namespace base {

void Delay(size_t time) {
  Sleep(static_cast<DWORD>(time));
}

} // namespace base

#endif // WIN32
