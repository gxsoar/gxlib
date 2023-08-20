#pragma once
#include <stdexcept>
#include <iostream>

namespace gxlib {
template<typename T>
struct allocator {
  // 开辟内存空间但是不涉及对象的构造
  T* allocate(size_t size) {
    return (T*)malloc(sizeof(T) * size);
  }
  // 释放内存空间
  void deallocate(void *p) {
    free(p);
  }
  // 负责构造对象
  void construct(T *p, const T& val) {
    new (p) T(val);
  }
  // 移动构造对象
  void construct(T* p, T&& val) {
    new (p) T(std::move(val));
  }
  // 负责对象的析构
  void destory(T* p) {
    p->~T();
  }
};
}