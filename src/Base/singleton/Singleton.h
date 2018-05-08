// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef BASE_SINGLETON_SINGLETON_H__
#define BASE_SINGLETON_SINGLETON_H__

#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>

#include "thread/Mutex.h"
#include "thread/MutexLocker.h"

/*
 * Place this macro in class definition for instantiation
 *
 * priority is the importance of the singleton. the higher priority a singleton has, the later
 * the singleton is deleted. Fundamental service singletons should have very high priority, say
 * 100 or even larger.
 *
 * SingletonManager is devided into two roles: SingletonMaster and SingletonSlave. The reason for
 * this is because DLLs have their own heap instead of sharing the one in the application
 * executable, which violates the singleton pattern. It's also possible that you manually created
 * a C/C++ Runtime Heap within the same module.
 *
 * SingletonMaster (generally) is called by application executable to set up a master copy of
 * singleton storage, which is later duplicated by SingletonSlaves in DLLs to maintain consistency.
 *
 * User tips:
 * (1) A SingletonManager(master or slave) must be in activated status in a heap while calling to
 *     Singleton::GetInstance().
 *
 * (2) SingletonManager(master or slave)'s Activate() and Shutdown() are not thread safe, and must
 *     be called within primary thread of heap owner when multi-thread mechanism is not in use.
 *     Activate() should be called only once in a heap.
 *
 * (3) Without explicit call to Shutdown(), SingletonManager will be shut down at the end of
 *     module(executable or DLL) life span: process termination or DLL unload. If you have other
 *     heap owner in the module, you must manually shut down SingletonManager.
 *
 * A typical usage:
 *
 * // Singleton user class
 * class SingletonUserClass : public Singleton {
 *   DECLARE_SINGLETON(SingletonUserClass)
 *
 *  public:
 *   void Function();
 *
 *  private:
 *   SingletonUserClass();
 *   ~SingletonUserClass();
 *
 * };
 *
 * // Singleton master generally is the application executable.
 * int main() {
 *   SingletonMaster::Activate();
 *
 *   SingletonUserClass *service = SingletonUserClass::GetInstance();
 *   service->Function();
 *
 *   // SingletonUserClass user; // Not possible
 *   // delete service; // Not Possible
 *
 *   return 0;
 * }
 *
 * // Singleton slaves generally are dynamic-link libraries.
 * void ModuleMainFunction(const SingletonMaster *master) {
 *   SingletonSlave::Activate(master);
 *
 *   SingletonUserClass *service = SingletonUserClass::GetInstance();
 *   service->Function();
 * }
 *
 */

// Normal priority with built-in creator
#define DECLARE_SINGLETON(class_name) \
DECLARE_SINGLETON_WITH_PRIORITY(class_name,0)

// User specified priority with built-in creator
#define DECLARE_SINGLETON_WITH_PRIORITY(class_name,priority) \
_DECLARE_SINGLETON_INTERNAL(class_name,priority) \
  static class_name *CreateInstance() { \
    return new class_name(); \
  }

// Normal priority with custom creator
// You must implement Singleton *Singleton::CreateInstance() method.
#define DECLARE_SINGLETON_WITH_CREATOR(class_name) \
_DECLARE_SINGLETON_INTERNAL(class_name,0) \
  static class_name *CreateInstance();

// User specified priority with custom creator
// You must implement Singleton *Singleton::CreateInstance() method.
#define DECLARE_SINGLETON_EX(class_name,priority) \
_DECLARE_SINGLETON_INTERNAL(class_name,priority) \
  static class_name *CreateInstance();

#define DECLARE_SINGLETON_DERIVED(class_name,base_class_name) \
_DECLARE_SINGLETON_DERIVED_INTERNAL(class_name,base_class_name) \
  static class_name *CreateInstance() { \
    return new class_name(); \
  }

#define DECLARE_SINGLETON_DERIVED_EX(class_name,base_class_name) \
_DECLARE_SINGLETON_DERIVED_INTERNAL(class_name,base_class_name) \
  static class_name *CreateInstance();

class Singleton;
class SingletonMaster;
class SingletonSlave;

namespace internal {

// Container class
class SingletonInstance {
 public:
  SingletonInstance(int priority, const std::string &name, Singleton *instance)
      : priority_(priority), name_(name), instance_(instance) {}

  bool operator < (const SingletonInstance &other) const {
    return priority_ < other.priority_;
  }

  int priority_;
  std::string name_;
  Singleton *instance_;

};

class SingletonManager {
 public:
  SingletonManager() : is_master_(false) {}

  // Only one SingletonMaster should exist in a process.
  void RunAsMaster();

  // Slave SingletonManagers must call this function once before any GetInstance() operations.
  void RunAsSlave(const SingletonMaster *master);

  // Destroy all singletons and data structures if it's master manager.
  void ShutdownSingletonManager();

  Mutex *singleton_mutex() const {
    return singleton_mutex_;
  }

  std::vector<internal::SingletonInstance> *singleton_instances() const {
    return singleton_instances_;
  }

 private:
  friend class ::Singleton;

  // Disable copy constructors
  explicit SingletonManager(const SingletonManager &);
  SingletonManager &operator = (const SingletonManager &);

  // Seek or create
  template <class _Ty>
  static _Ty *GetInstance(const std::string &name, int priority) {
    assert(singleton_mutex_);
    assert(singleton_instances_);
    MutexLocker locker(singleton_mutex_);

    size_t base_pos = name.find_first_of('.') + 1;
    assert(base_pos > 0);

    for (std::vector<SingletonInstance>::iterator p = singleton_instances_->begin();
        p != singleton_instances_->end(); ++p) {
      if (p->name_.compare(0, base_pos, name, 0, base_pos) == 0) {
        // Topmost base class exists
        if (p->name_.compare(0, name.length(), name) == 0) {
          // Existing one is the same type or derived object.
          _Ty *instance = reinterpret_cast<_Ty *>(p->instance_);
          return instance;
        } else {
          // Existing singleton object cannot be converted into requesting type.
          assert(false);
          return NULL;
        }
      }
    }

    // Topmost base class doesn't exist, create one.
    _Ty *instance = _Ty::CreateInstance();
    singleton_instances_->push_back(SingletonInstance(priority, name, instance));
    return instance;
  }

  static Mutex *singleton_mutex_;
  static std::vector<SingletonInstance> *singleton_instances_;

  bool is_master_;

};

} // namespace internal

class Singleton {
 public:
  virtual ~Singleton() {}

 protected:
  // Simple delegate to keep SingletonManager::GetInstance() private.
  template <class _Ty>
  static _Ty *GetInstance(const std::string &name, int priority) {
    return ::internal::SingletonManager::GetInstance<_Ty>(name, priority);
  }

};

#define _DECLARE_SINGLETON_INTERNAL(class_name,priority) \
 public: \
  friend class ::internal::SingletonManager; \
  static class_name *GetInstance() { \
    return Singleton::GetInstance<class_name>(#class_name ".", priority); \
  } \
 protected: \
  static void CreateSingletonName(std::string &result) { \
    result = #class_name "."; \
  } \
  static const int SINGLETON_PRIORITY = priority; \
 private: \
  explicit class_name(const class_name &); \
  class_name &operator = (const class_name &);

#define _DECLARE_SINGLETON_DERIVED_INTERNAL(class_name,base_class_name) \
 public: \
  friend class ::internal::SingletonManager; \
  static class_name *GetInstance() { \
    std::string name; \
    CreateSingletonName(name); \
    return Singleton::GetInstance<class_name>(name, SINGLETON_PRIORITY); \
  } \
 protected: \
  static void CreateSingletonName(std::string &result) { \
    base_class_name::CreateSingletonName(result); \
    result.append(#class_name "."); \
  } \
 private: \
  explicit class_name(const class_name &); \
  class_name &operator = (const class_name &);

#endif // BASE_SINGLETON_SINGLETON_H__
