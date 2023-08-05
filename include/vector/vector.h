#pragma once

namespace gxlib {

template<typename T>
class vector {
public:
  using value_type = T;
  using iterator = T*;
  vector() : data_(nullptr), size_(0), capactiy_(0) {}
  ~vector() {
    if (data_) {
      delete [] data_;
      size_ = 0;
      capactiy_ = 0;
    }
  }
  // 拷贝构造函数
  vector(const vector &rhs) {
    size_ = rhs.size_;
    capactiy_ = rhs.capactiy_;
    data_ = new value_type[capactiy_];
    for (int i = 0; i < size_; ++ i) {
      data_[i] = rhs.data_[i];
    }
  }
  // 拷贝赋值构造
  vector& operator=(const vector &rhs) {
    if (this == &rhs) return *this;
    value_type *tmp = new value_type[capactiy_];
    for (int i = 0; i < rhs.size_; ++ i) {
      tmp[i] = rhs.data_[i];
    }
    delete [] data_;
    data_ = tmp;
    size_ = rhs.size_;
    capactiy_ = rhs.capactiy_;
    return *this;
  }
  // 移动构造函数
  vector(vector &&rhs) {
    data_ = rhs.data_;
    rhs.data_ = nullptr;
  }
  // 重载下标运算符
  vector& operator[](int index) {
    return data_[index];
  }
  // 定义push_back函数
  void push_back(value_type val) {
    // 执行二倍扩容策略
    if (size_ == capactiy_) {
      int new_capacity = capactiy_ == 0 ? 1 : 2 * capactiy_;
      value_type *new_data = new value_type[new_capacity];
      for (int i = 0; i < size_; ++ i) {
        new_data[i] = data_[i];
      }
      delete [] data_;
      data_ = new_data;
      capactiy_ = new_capacity;
    }
    data_[size_++] = val;
  }
  void pop_back() {
    if (size_ > 0) --size_;
  }
  // 返回首元素位置
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }
  int size() const { return size_; }
  int capacity() const { return capactiy_; }
  bool empty() { return size_ == 0; }
  value_type& front() { return &data_[0]; }
  value_type& back() { return &data[size_ - 1]; }
private:
  value_type *data_;
  int size_;
  int capactiy_;
};

}