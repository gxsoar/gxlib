#include "designpattern/proxy/proxy.h"

namespace gxlib {
int main() {
  ConcreteSubject* real_subject = new ConcreteSubject;

  std::unique_ptr<Proxy> proxy = std::make_unique<Proxy>(real_subject);
  proxy->request();

  return 0;
}
}