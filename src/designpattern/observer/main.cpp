#include "designpattern/observer/observer.h"

int main(int argc, char const *argv[])
{
  WeatherStation ws; // 创建一个具体的主题对象
  // 创建一个观察者对象，并观察ws
  CurrentConditionDisplay ccd(&ws);

  ws.measurements_changed(0.01, 0.02, 0.03);
  return 0;
}
