#pragma once
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "allocator.h"

namespace gxlib {

template<typename T>
class new_vector {
public:
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;
  // 构造函数
  new_vector() : elements_(nullptr), first_free_(nullptr), cap_(nullptr) {}
  // 带有参数的构造函数
  new_vector(size_type n, const T& val = T()) : elements_(nullptr), first_free_(nullptr), cap_(nullptr) {
    reserve(n); // 分配空间，然后插入初始化元素
  
  }
  new_vector(const new_vector& v) : elements_(nullptr), first_free_(nullptr), cap_(nullptr) {
    // 重新分配空间
    reserve(v.size());
    std::uninitialized_copy(v.begin(), v.end(), elements_);
    first_free_ = cap_ = elements_ + v.size();
  }
  // 移动构造
  new_vector(new_vector&& v) noexcept : elements_(v.elements_), first_free_(v.first_free_), cap_(v.cap_) {
    // 移动之后将原来的指针置为空
    v.elements_ = v.first_free_ = v.cap_ = nullptr;
  }
  // 释放内存空间
  ~new_vector() {
    free();
  }
  // 赋值运算符
  new_vector& operator=(const new_vector& v) {
    if (this != &v) {
      // 先释放原有的内存空间
      free();
      reserve(v.size());  // 构造新的空间
      std::uninitialized_copy(v.begin(), v.end(), elements_);
      first_free_ = cap_ = elements_ + v.size();
    }
    return *this;
  }
  // 移动赋值运算符
  new_vector& operator=(new_vector&& v) {
    if (this != v) {
      // 释放原有空间
      free();
      elements_ = v.elements_;
      first_free_ = v.first_free_;
      cap_ = v.cap_;
      v.elements_ = v.first_free_ = v.elements_ = nullptr;  // 移动后原来的指针设置为空
    }
  }
  // 重载下标运算符
  T& operator[](int n) { return elements_[n]; }
  const T& operator[](int n) const { return elements_[n]; }
  T& front() { return *elements_; }
  const T& front() const { return *elements_; }
  T& back() { return *(first_free_ - 1); }
  const T& back() const { return *(first_free_ - 1); }

  // 迭代器
  iterator begin() { return elements_; }
  iterator begin() const { return elements_; }
  iterator end() { return first_free_; }  // 返回尾部元素的下一个位置
  iterator end() const { return first_free_; }
  size_type capacity() const { return cap_ - elements_; }
  size_type size() const { return elements_ - first_free_; }
  bool empty() const { return elements_ == first_free_; }
  void reserve(size_type n) {
    if (n > capacity()) {
      // 当n比现有的空间还要大是分配更多的内存空间
      auto new_data = alloc.allocate(n);
      auto dest = new_data;
      auto elem = elements_;  // 指向旧空间的首位置
      // 将原来的对象移动到新的空间
      for (size_type i = 0; i != size(); ++ i) {
        alloc.construct(dest++, std::move(*elem++));
      }
      // 释放旧的内存空间
      free();
      elements_ = new_data;
      first_free_ = dest;
      cap_ = elements_ + n
    }
  }
  void resize(size_type n, const T& val = T()) {
    if (n <= size()) { // 缩小容量
      for (auto p = elements_ + n; p != first_free_; ++ p) {
        // 销毁多余元素, 注意只是销毁多余元素，但是没有释放内存空间
        alloc.destory(p);
      }
      first_free_ = elements_ + n;
    } else (n > size()) {
      reserve(n); // 重新分配空间
      for (size_type i = size(); i < n; ++ i) {
        alloc.construct(first_free_++, val);  // 构造新元素
      }
    }
  } 
  void shrink_to_fit() {
    if (first_free_ != cap_) {  // 只有在有多余的空间才有用
      auto new_data = alloc.allocate(size());
      auto dest = new_data; // 指向新空间的受位置
      auto elem = elements_; // 旧空间首位置
      for (size_type i = 0; i != size(); ++ i) {
        alloc.construct(dest++, std::move(*elem++));  // 移动旧元素到新空间
      }
      free(); //释放旧空间
      elements_ = new_data;
      first_free_ = cap = dest;
    }
  }
  void clear() { free(); }
  void push_back(const T& val) {
    check_n_alloc();  // 检查并分配内存空间
    // 在尾部构造并添加元素
    alloc.construct(first_free_++, val);
  }
  void pop_back() {
    if (!empty()) {
      // 释放尾部元素
      alloc.destory(--first_free_);
    }
  }
private:
  void check_n_alloc() {
    if (size() == capacity()) {
      
    }
  }
  void reallocate() {
    auto new_capacity = size() ? 2 * size() : 1; // 新空间是旧空间的两倍或者为1
    reserve(new_capacity);
  }
  void free() {
    // 只有非空的时候才能释放
    if (elements_) {
      // 先销毁其中的对象
      for (auto p = first_free_; p != elements_;) {
        alloc.destory(--p);
      }
      // 再调用析构函数释放内存空间
      for (auto p = cap_; p != elements_;) {
        alloc.deallocate(--p);
      }
    }
  }
private:
  T* elements_;
  T* first_free_;
  T* cap_;
  // 分配器，用于分配和释放内存以及构造和销毁对象
  allocator<T> alloc;
};

};