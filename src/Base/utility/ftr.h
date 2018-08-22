// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef BASE_UTILITY_FTR_H__
#define BASE_UTILITY_FTR_H__

#include <assert.h>

#include <string>

#ifdef USE_QT_TRANSLATE
#include <QtCore/QCoreApplication>
#endif // USE_QT_TRANSLATE

static const char *FTR_CONTEXT = "FTR";

inline std::string ftr(const char *context, const char *src) {
  if (!src) {
    assert(false);
    return "";
  }

#ifndef USE_QT_TRANSLATE
  return src;
#else
  return QCoreApplication::translate(context, src).toStdString();
#endif // USE_QT_TRANSLATE
}

inline std::string ftr(const char *src) {
  return ftr(FTR_CONTEXT, src);
}

#endif // BASE_UTILITY_FTR_H__
