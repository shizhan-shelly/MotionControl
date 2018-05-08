// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef BASE_SINGLETON_SINGLETONSLAVE_H__
#define BASE_SINGLETON_SINGLETONSLAVE_H__

#include "Singleton.h"
#include "SingletonMaster.h"

class SingletonSlave {
 public:
  static void Activate(const SingletonMaster *master);

  static void Shutdown() {
    slave_.manager_.ShutdownSingletonManager();
  }

 private:
  SingletonSlave() : activated_(false) {}

  ~SingletonSlave() {
    if (activated_) {
      Shutdown();
    }
  }

  static SingletonSlave slave_;

  internal::SingletonManager manager_;
  bool activated_;

};

#endif // BASE_SINGLETON_SINGLETONSLAVE_H__
