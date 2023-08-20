#pragma once

#include <cstring>

namespace gxlib {

class string {
public:
  // 定义无参构造函数
  string() : str_(new char[1]), len_(0) {
    str_[0] = '\0';
  }
  // 定义拷贝构造函数
  string(const string &rhs) {
    str_ = new char[rhs.len_];
    len_ = rhs.len_;
    strcpy(str_, rhs.str_);
  }
  // 定义从C风格的拷贝构造函数
  string(const char *s) {
    str_ = new char[strlen(s) + 1];
    len_ = strlen(s);
    strcpy(str_, s);
  }
  // 定义从字符串和重复字数的构造函数
  string(char c, int n) {
    str_ = new char[n + 1];
    for (int i = 0; i < n; ++ i) {
      str_[i] = c;
    }
    str_[n] = '\0';
  }
  // 析构函数
  ~string() {
    delete [] str_;
    len_ = 0;
    str_ = nullptr;
  }
  // 定义移动构造函数
  string(string &&rhs) {
    str_ = rhs.str_;
    if (str_) {
      rhs.str_ = nullptr;
    }
  }
  // 定义赋值构造函数
  string& operator=(const string &rhs) {
    if (this != &rhs) {
      char *tmp = new char[rhs.len_ + 1];
      strcpy(tmp, rhs.str_);
      delete str_;
      str_ = tmp;
      len_ = rhs.len_;
    }
    return *this;
  }
  // 定义加法运算符
  string operator+(const string &rhs) {
    string tmp;
    tmp.len_ = len_ + rhs.len_;
    tmp.str_ = new char[tmp.len_ + 1];
    strcpy(tmp.str_, str_);
    strcat(tmp.str_, rhs.str_);
    return tmp;
  }

  // 定义下标运算符
  char& operator[](int index) {
    return str_[index];
  }
  int size() const { return len_; }
  bool empty() const { return len_ == 0; }
  const char* c_str() const { return str_; }
  void append(const string &rhs) {
    *this = *this + rhs;
  }
  void insert(int pos, const string &rhs) {
    if (pos < 0 || pos > len_) return;
    string tmp = *this;
    len_ += rhs.len_;
    delete [] str_;
    str_ = new char[len_ + 1];
    strncpy(tmp.str_, str_, pos);
    strcat(str_, rhs.str_);
    strcat(str_, tmp.str_ + pos);
  }
  void erase(int pos, int n) {
    if (pos < 0 || pos >= len_ || n <= 0) return;
    if (pos + n >= len_) n = len_ - pos;
    strcpy(str_ + pos, str_ + pos + n);
    len_ -= n;
  }
private:
  char *str_; // 指向动态分配的字符数组
  int len_; // 记录字符串长度
};

}