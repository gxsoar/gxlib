#pragma once

#include <iostream>
#include <mutex>

namespace gxlib {

// 饿汉单例模式
class EagerSingleInstance {
public:
  static EagerSingleInstance* GetInstance() {
    static EagerSingleInstance ins;
    return &ins;
  }
  ~EagerSingleInstance();
private:
  EagerSingleInstance() { std::cout << "SingleInstance() eager\n"; }
  EagerSingleInstance(const EagerSingleInstance& rhs) {};
  EagerSingleInstance& operator=(const EagerSingleInstance& rhs) {
    return *this;
  }
};

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