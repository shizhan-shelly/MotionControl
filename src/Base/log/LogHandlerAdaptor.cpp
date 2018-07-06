// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "base/log/LogHandlerAdaptor.h"

namespace base {

LogHandlerAdaptor::~LogHandlerAdaptor() {
  for (size_t i = 0; i < handlers_.size(); i++) {
    delete handlers_[i];
  }
}

void LogHandlerAdaptor::Handle(const Logger *logger, const LogEntry &entry) {
  for (size_t i = 0; i < handlers_.size(); i++) {
    handlers_[i]->Handle(logger, entry);
  }
}

} // namespace base
