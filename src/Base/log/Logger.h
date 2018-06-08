// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef BASE_LOG_LOGGER_H__
#define BASE_LOG_LOGGER_H__

#include <assert.h>

#include <string>
#include <vector>

#include "base/log/Log.h"

namespace base {

class LogHandler;

/**
 * Logger is the front end for users writing log informations.
 * @warning: Logger is not thread safe by design, create and maintain your own copy.
 */
class Logger {
 public:
  /// Top level logger, no parent present.
  /// @param: handlers are the actual log handlers.
  /// @param: name is the name of the logger which will be later added into descriptions.
  /// @param: filter is the level that any logs lower than it will be ignored.
  Logger(const std::vector<LogHandler *> &handlers, const std::string &name,
         const LogLevel &filter = LogLevelInformation);

  /// Child logger object which inherits parent properties.
  Logger(const Logger &parent);
  Logger(const Logger *parent);

  ~Logger();

  /// Get the formatted name of log.
  /// @example: base_name[1]
  const std::string &name() const {
    return name_;
  }

  void error(const std::string &log) {
    return write(LogLevelError, log);
  }

  void warning(const std::string &log) {
    return write(LogLevelWarning, log);
  }

  void information(const std::string &log) {
    return write(LogLevelInformation, log);
  }

  void debug(const std::string &log) {
    return write(LogLevelDebug, log);
  }

 private:
  void InitName();

  /// Write a log entry with specified log level.
  /// @param level is the log level, lower level than filter level will be ignored.
  /// @param log is the content to log.
  /// @sa Receiptor::arg
  void write(const LogLevel &level, const std::string &log);

  const std::string base_name_;
  const Logger *const parent_;
  std::vector<LogHandler *> handlers_;
  const LogLevel filter_;
  std::string name_;
  const int depth_;

}; // class Logger

} // namespace base

#endif BASE_LOG_LOGGER_H__
