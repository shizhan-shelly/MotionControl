// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef BASE_LOG_LOGENTRY_H__
#define BASE_LOG_LOGENTRY_H__

#include <ctime>
#include <string>

#include "base/log/Log.h"

namespace base {

class LogEntry {
 public:
  LogEntry(const std::time_t &timestamp, const LogLevel &level,
           const std::string &log)
      : timestamp_(timestamp), level_(level), log_(log) {}

  std::time_t timestamp() const {
    return timestamp_;
  }

  LogLevel level() const {
    return level_;
  }

  const std::string &log() const {
    return log_;
  }

 private:
  LogLevel level_;
  std::string log_;
  std::time_t timestamp_;

}; // class LogEntry

} // namespace base

#endif BASE_LOG_LOGENTRY_H__
