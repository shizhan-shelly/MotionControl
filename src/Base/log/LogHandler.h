// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef BASE_LOG_LOGHANDLER_H__
#define BASE_LOG_LOGHANDLER_H__

#include "base/log/LogEntry.h"

namespace base {

class Logger;

class LogHandler {
 public:
  virtual ~LogHandler();
  virtual void Handle(const Logger *logger, const LogEntry &entry) = 0;

}; // class LogHandler

} // namespace base

#endif BASE_LOG_LOGHANDLER_H__
