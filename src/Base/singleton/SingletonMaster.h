// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef BASE_SINGLETON_SINGLETONMASTER_H__
#define BASE_SINGLETON_SINGLETONMASTER_H__

#include "base/singleton/Singleton.h"

class SingletonMaster {
 public:
  static void Activate();

  static SingletonMaster *GetInstance() {
    return &master_;
  }

  static void Shutdown() {
    master_.manager_.ShutdownSingletonManager();
  }

  Mutex *singleton_mutex() const {
    return singleton_mutex_;
  }

  std::vector<internal::SingletonInstance> *singleton_instances() const {
    return singleton_instances_;
  }

 private:
  SingletonMaster() : activated_(false) {}

  ~SingletonMaster() {
    if (activated_) {
      Shutdown();
    }
  }

  static SingletonMaster master_;

  internal::SingletonManager manager_;
  std::vector<internal::SingletonInstance> *singleton_instances_;
  Mutex *singleton_mutex_;
  bool activated_;

};

#endif // BASE_SINGLETON_SINGLETONMASTER_H__
