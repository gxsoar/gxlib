#pragma once

#include <algorithm>

namespace gxlib {

template <typename T>
class unique_ptr {
public:
  explicit unique_ptr(T* ptr == nullptr) : ptr_(ptr) {}
  ~unique_ptr() {
    del();
  }
  void del() {
    if (ptr_ != nullptr) {
      delete ptr_;
    }
  }
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&)=delete;
  // 移动构造函数
  unique_ptr(unique_ptr&& rhs) {
    ptr_ = rhs.release();
  }
  // 能够进行子类到基类类型转换的移动构造函数
  template<typename U>
  unique_ptr(unique_ptr<U>&& rhs) {
    ptr_ = rhs.ptr_;
    if (ptr_)  {
      rhs.ptr_ = nullptr;
    }
  }
  T* release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }
  void reset(T* other) {
    if (ptr_ != other) {
      del();
      ptr_ = other;
    }
  }
  void swap(unique_ptr& rhs) {
    using std::swap;
    swap(ptr_, rhs.ptr_);
  }
  T* get() { return ptr_; }
  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
private:
  T* ptr_;
};

}