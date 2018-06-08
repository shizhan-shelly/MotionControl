// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "base/log/Logger.h"

#include <sstream>

#include "base/log/LogHandler.h"

namespace base {

Logger::Logger(const std::vector<LogHandler *> &handlers,
               const std::string &name,
               const LogLevel &filter) : base_name_(name)
                                       , parent_(NULL)
                                       , handlers_(handlers)
                                       , filter_(filter)
                                       , depth_(1) {

  assert(name.length());
  InitName();
}

Logger::Logger(const Logger &parent) : base_name_(parent.base_name_)
                                     , parent_(&parent)
                                     , handlers_(parent.handlers_)
                                     , filter_(parent.filter_)
                                     , depth_(parent.depth_ + 1) {

  InitName();
}

Logger::Logger(const Logger *parent) : base_name_(parent->base_name_)
                                     , parent_(parent)
                                     , handlers_(parent->handlers_)
                                     , filter_(parent->filter_)
                                     , depth_(parent->depth_ + 1) {

  assert(parent);
  InitName();
}

Logger::~Logger() {}

void Logger::InitName() {
  std::stringstream s;
  s << base_name_ << '[' << depth_ << ']';
  name_ = s.str();
}

void Logger::write(const LogLevel &level, const std::string &log) {
  if (level >= filter_) {
    std::time_t time;
    std::time(&time);
    LogEntry entry(time, level, log);
    for (size_t i = 0; i< handlers_.size(); i++) {
      handlers_[i]->Handle(this, entry);
    }
  }
}

} // namespace base
