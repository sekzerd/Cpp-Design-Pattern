#include <iostream>
#include <string>
class subsystem_A {
public:
  virtual void operation() {
    std::cout << "subsystem_A operation()" << std::endl;
  }
  virtual ~subsystem_A() {}
};

class subsystem_B {
public:
  virtual void operation() {
    std::cout << "subsystem_B operation()" << std::endl;
  }
  virtual ~subsystem_B() {}
};
class facade : public subsystem_A, public subsystem_B {
private:
  subsystem_A *m_subsystem_A;
  subsystem_B *m_subsystem_B;

public:
  facade()
      : m_subsystem_A(new subsystem_A()), m_subsystem_B(new subsystem_B()) {}
  void operation_A() {
    if (m_subsystem_A) {
      m_subsystem_A->operation();
    }
  }
  void operation_B() {
    if (m_subsystem_B) {
      m_subsystem_B->operation();
    }
  }

  ~facade() {
    if (m_subsystem_A) {
      delete m_subsystem_A;
    }
    if (m_subsystem_B) {
      delete m_subsystem_B;
    }
  }
};
int main(const int argc, const char **argv) {
  facade *_facade = new facade();
  _facade->operation_A();
  _facade->operation_B();

  delete _facade;

  return 0;
}