#include <iostream>
#include <string>
class target {
public:
  virtual void request() = 0;
  virtual ~target() {}
};
class adaptee {
public:
  void specific_request() {
    std::cout << "adaptee specific_request()" << std::endl;
  }
  virtual ~adaptee() {}
};
class adapter : public target, public adaptee {
public:
  virtual void request() override { specific_request(); }
};
int main(const int argc, const char **argv) {
  target *target = new adapter();
  target->request();
  if (target) {
    delete target;
  }
  return 0;
}