#include "designpattern/single_instance/single_instance.h"

namespace gxlib {
// 静态变量需要初始化
LazySingleInstance* LazySingleInstance::ins = nullptr;
std::mutex LazySingleInstance::mutex_;

int main() {
  EagerSingleInstance* eager_ins = EagerSingleInstance::GetInstance();
  LazySingleInstance* lazy_ins = LazySingleInstance::GetInstance();
  delete eager_ins;
  delete lazy_ins;
  return 0;
}
}