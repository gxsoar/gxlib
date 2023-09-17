#pragma once

#include <algorithm>

namespace gxlib {

class shared_count {
public:
  shared_count() : count_(1) {}
  void add_count() {
    count_++;
  }
  long long reduce_count() {
    --count_;
  }
  long long get_count() const {
    return count_;
  }
private:
  long long count_;
};

template <typename T>
class shared_ptr {
public:
  template<typename U>
  friend class shared_ptr;

  explicit shared_ptr(T* ptr = nullptr) : ptr_(ptr) {
    if (ptr) {
      shared_count_ = new shared_count();
    }
  }

  shared_ptr(const shared_ptr& rhs) {
    ptr_ = rhs.ptr_;
    if (ptr_) {
      rhs.shared_count_->add_count();
      shared_count_ = rhs.shared_count_;
    }
  }

  template<typename U>
  shared_ptr(const shared_ptr<U>& rhs) {
    ptr_ = rhs.ptr_;
    if (ptr_) {
      rhs.shared_count_->add_count();
      this->shared_count_ = rhs.shared_count_;
    }
  }

  // 移动构造函数
  shared_ptr(shared_ptr&& rhs) {
    ptr_ = rhs.release(); // 释放所有权并返回裸指针
  }

  // 为了实现子类向基类的转换, 这个函数不会被看作移动构造函数
  // 不会造成删除构造函数的行为
  template<typename U>
  shared_ptr(shared_ptr<U>&& rhs) {
    ptr_ = rhs.ptr_;
    if (ptr_) {
      shared_count_ = rhs.shared_count_;
      rhs.ptr_ = nullptr;
    }
  }

  template<typename U>
  shared_ptr(const shared_ptr<U>& rhs, T* ptr) {
    ptr_ = ptr;
    if (ptr_) {
      rhs.shared_count_->add_count();
      shared_count_ = rhs.shared_count_;
    }
  }

  long long use_count() const {
    if (ptr_) {
      return shared_count_->get_count();
    } else {
      return 0;
    }
  }

  // 采用赋值操作, 在这里面经过了一次拷贝，引用计数已经加一
  shared_ptr& operator=(shared_ptr rhs) {
    rhs.swap(*this);
    return *this;
  }

  
  T* release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }

  void swap(shared_ptr& rhs) {
    using std::swap;
    swap(ptr_, rhs.ptr_);
    swap(shared_count_, rhs.shared_count_);
  }

  ~shared_ptr() { 
    if (ptr_ && !shared_count_->reduce_count()) {
      delete ptr_;
      delete shared_count_;
    }
  }
  T* get() { return ptr_; }
  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  operator bool() const { return ptr_; }
private:
  T* ptr_;
  shared_count* shared_count_;
};

}