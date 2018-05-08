// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#include "Singleton.h"
#include "SingletonMaster.h"

namespace internal {

// Only one SingletonMaster should exist in a process.
void SingletonManager::RunAsMaster() {
  assert(singleton_instances_ == NULL);

  singleton_mutex_ = new Mutex;
  singleton_instances_ = new std::vector<SingletonInstance>;
  is_master_ = true;
}

// Slave SingletonManagers must call this function once before any GetInstance() operations.
void SingletonManager::RunAsSlave(const SingletonMaster *master) {
  assert(master);
  if (singleton_instances_ == NULL) {
    singleton_mutex_ = master->singleton_mutex();
    singleton_instances_ = master->singleton_instances();
    is_master_ = false;
  }
}

// Destroy all singletons and data structures if it's master manager.
void SingletonManager::ShutdownSingletonManager() {
  if (!singleton_instances_) {
    return;
  }

  assert(singleton_instances_);
  assert(singleton_mutex_);

  // Only master can destroy singletons and data structure.
  if (is_master_) {
    // Ensure low priority first
    std::reverse(singleton_instances_->begin(), singleton_instances_->end());
    std::stable_sort(singleton_instances_->begin(), singleton_instances_->end());

    for (std::vector<SingletonInstance>::iterator p = singleton_instances_->begin();
        p != singleton_instances_->end(); ++p) {
      Singleton *instance = p->instance_;
      assert(instance);
      delete instance;
    }
    delete singleton_instances_;
    delete singleton_mutex_;
  }
  is_master_ = false;
  singleton_instances_ = NULL;
  singleton_mutex_ = NULL;
}

Mutex *SingletonManager::singleton_mutex_ = NULL;
std::vector<SingletonInstance> *SingletonManager::singleton_instances_ = NULL;

} // namespace internal
