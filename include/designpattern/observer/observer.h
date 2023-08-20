#pragma once

#include <iostream>
#include <vector>
#include <set>

// 定义一个抽象的观察者接口
class Observer {
public:
  virtual void update(float temp, float humidity, float pressure) = 0;
};

// 定义抽象主题接口
class Subject {
public:
  virtual void attach(Observer *) = 0;
  virtual void detach(Observer *) = 0;
  virtual void notify_observers() = 0;
};

// 具体主题类
class WeatherStation : public Subject {
private:
  std::set<Observer*> observers_;  // 观察者集合
  float temperature_;   // 状态数据
  float humidity_;    // 状态数据
  float pressure_;    // 数据
public:
  // 注册一个观察者到集合当中
  void attach(Observer *o) override {
    observers_.insert(o);
  }
  // 从集合中注销一个观察者
  void detach(Observer *o) override {
    if (observers_.count(o) != 0) {
      observers_.erase(o);
    }
  }
  // 通知所有观察者当前的数据
  void notify_observers() override {
    for (auto &observer : observers_) {
      observer->update(temperature_, humidity_, pressure_);
    }
  }

  // 设置新的状态数据并调用通知方法
  void measurements_changed(float temp, float humi, float pres) {
    temperature_ = temp;
    humidity_ = humi;
    pressure_ = pres;
    notify_observers();
  }
};

// 具体的观察者
class CurrentConditionDisplay : public Observer {
public:
  // 构造函数传入一个被观察到对象
  CurrentConditionDisplay(Subject* ws) : weather_station_(ws) {
    weather_station_->attach(this);
  }
  // 更新本地数据状态并显示
  void update(float temp, float humi, float pres) override {
    temperature_ = temp;
    humidity_ = humi;
    display();
  }
  void display() {
    std::cout << "Current conditions: " << temperature_ << " C degrees and "
                  << humidity_ << "% humidity" << std::endl;
  }
private:
  Subject* weather_station_;  // 对所观察的主题对象的引用
  float temperature_;
  float humidity_;
};

