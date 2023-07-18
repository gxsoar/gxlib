#pragma once

#include <iostream>
#include <memory>
namespace gxlib{

class Subject {
public:
  virtual void request() = 0;
  virtual ~Subject() {};  // 定义虚析构函数
};

class ConcreteSubject : public Subject {
public:
  void request() override {
    std::cout << "ConcreteSubject: Handling request\n";
  }
};

class Proxy : public Subject {
private:
  std::unique_ptr<Subject> subject_;

public:
  Proxy(Subject* subject) : subject_(subject) {}
  void request() override {
    std::cout << "Proxy: Checking access prior to firing a real request\n";
    subject_->request();
    std::cout << "Proxy: logging\n";
  }
};

}
