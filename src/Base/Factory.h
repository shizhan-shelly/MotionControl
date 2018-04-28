// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef  BASE_FACTORY_H__
#define  BASE_FACTORY_H__

#define DECLARE_FACTORY(class_name) \
 public: \
  static class_name *CreateInstance(); \
 private: \
  explicit class_name(const class_name &); \
  class_name &operator = (const class_name &);

#endif  // BASE_FACTORY_H__
