// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef BASE_LOG_LOGHANDLERADAPTOR_H__
#define BASE_LOG_LOGHANDLERADAPTOR_H__

#include <vector>

#include "base/log/LogHandler.h"

namespace base {

/**
 * LogHandlerAdaptor is a adaptor to a series of LogHandlers.
 * Use Add() to insert handlers to LogHandlerAdaptor.
 * Call Handle() to handle all the saved handlers.
 * @warning After Add(), the life span of the added handler should be controlled by
 * LogHandlerAdaptor.
 */
class LogHandlerAdaptor : public LogHandler {
 public:
  ~LogHandlerAdaptor();

  virtual void Handle(const Logger *logger, const LogEntry &entry);

  const std::vector<LogHandler *> &handlers() const {
    return handlers_;
  }

  /// LogHandlerAdaptor is responsible for the life span of handlers_.
  void Add(LogHandler *handler) {
    handlers_.push_back(handler);
  }

 private:
  explicit LogHandlerAdaptor(const LogHandlerAdaptor &);
  LogHandlerAdaptor &operator = (const LogHandlerAdaptor &);

  std::vector<LogHandler *> handlers_;

}; // class LogHandlerAdaptor

} // namaspace base

#endif // BASE_LOG_LOGHANDLERADAPTOR_H__
