#pragma once

#include <iostream>
#include <mutex>

namespace gxlib {

// 懒汉单例模式，线程不安全
class SingleInstance {
public:
  static SingleInstance *GetInstance() {
    if (m_SingleInstance == nullptr) {
      m_SingleInstance = new SingleInstance();
    }
    return m_SingleInstance;
  }
  static void deleteInstance() {
    if (m_SingleInstance != nullptr) {
      delete m_SingleInstance;
      m_SingleInstance = nullptr;
    }
  }
private:
  SingleInstance();
  ~SingleInstance();
  SingleInstance(const SingleInstance &rhs);
  const SingleInstance &operator=(const SingleInstance &rhs);
private:
  static SingleInstance *m_SingleInstance;
};

// 懒汉单例，不加锁线程安全
class SingleInstance {
public:
  static SingleInstance *GetInstance() {
    static SingleInstance single;
    return &single;
  }
private:
  SingleInstance();
  ~SingleInstance();
  SingleInstance(const SingleInstance &rhs);
  const SingleInstance &operator=(const SingleInstance &rhs);
};

// 饿汉单例模式, 加锁线程安全
class EagerSingleInstance {
public:
  static EagerSingleInstance* GetInstance() {
    return single_instance_;
  }
  ~EagerSingleInstance();
private:
  EagerSingleInstance() { std::cout << "SingleInstance() eager\n"; }
  EagerSingleInstance(const EagerSingleInstance& rhs) {};
  EagerSingleInstance& operator=(const EagerSingleInstance& rhs) {
    return *this;
  }
private:
  static EagerSingleInstance *single_instance_;
};
// 代码一运行就立刻初始化
EagerSingleInstance* EagerSingleInstance::single_instance_ = new (std::nothrow)EagerSingleInstance();

// 懒汉单例模式
class LazySingleInstance {
public:
  static std::mutex mutex_;
  static LazySingleInstance* GetInstance() {
    if (ins == nullptr) {
      std::lock_guard<std::mutex> lk{mutex_};
      if (ins == nullptr) {
        ins = new LazySingleInstance();
      }
    }
    return ins;
  }
  ~LazySingleInstance();
private:
  LazySingleInstance() { std::cout << "SingleInstance() lazy\n"; }
  LazySingleInstance(const LazySingleInstance& rhs) {};
  LazySingleInstance& operator=(const LazySingleInstance& rhs) {
    return *this;
  }
  static LazySingleInstance* ins;
};

} // namespace gxlib