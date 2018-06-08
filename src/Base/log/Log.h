// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef BASE_LOG_LOG_H__
#define BASE_LOG_LOG_H__

namespace base {

typedef unsigned int LogId;
typedef std::string LogArgument;

// LOG_UNIQUE_ID_BITS is always LOG_DATABASE_ID_BITS + LOG_ID_BITS
#define LOG_UNIQUE_ID_BITS       32
#define LOG_DATABASE_ID_BITS     12
#define LOG_ID_BITS              20

typedef enum _LogLevel {
  LogLevelDebug,
  LogLevelInformation,
  LogLevelWarning,
  LogLevelError,

} LogLevel;

} // namespace base

#endif BASE_LOG_LOG_H__
