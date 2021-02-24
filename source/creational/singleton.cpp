#include <iostream>
#include <string>
class singleton {
private:
  static singleton *singleton_ptr;

protected:
  singleton() {}

public:
  singleton(const singleton &) = delete;
  singleton &operator=(const singleton &) = delete;
  static singleton *get_instance();
  void do_something();
};
singleton *singleton::singleton_ptr = nullptr;
singleton *singleton::get_instance() {
  if (!singleton_ptr) {
    singleton_ptr = new singleton;
  }
  return singleton_ptr;
}
void singleton::do_something() {
  std::cout << "singleton do something" << std::endl;
}
int main(const int argc, const char **argv) {
  singleton *one_instance = singleton::get_instance();
  one_instance->do_something();

  delete one_instance;

  return 0;
}