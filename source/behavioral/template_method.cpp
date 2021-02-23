#include <iostream>

class abstract_class {
public:
  void template_method() {
    primitive_operation_1();
    primitive_operation_2();
  }
  virtual ~abstract_class() {}

protected:
  virtual void primitive_operation_1() = 0;
  virtual void primitive_operation_2() = 0;
};

class concrete_class_typeA : public abstract_class {
public:
  concrete_class_typeA() {}
  void primitive_operation_1() override {
    std::cout << "concrete_class_typeA primitive_operation_1()" << std::endl;
  }
  void primitive_operation_2() override {
    std::cout << "concrete_class_typeA primitive_operation_2()" << std::endl;
  }
  ~concrete_class_typeA() {}
};

class concrete_class_typeB : public abstract_class {
public:
  concrete_class_typeB() {}
  void primitive_operation_1() override {
    std::cout << "concrete_class_typeB primitive_operation_1()" << std::endl;
  }
  void primitive_operation_2() override {
    std::cout << "concrete_class_typeB primitive_operation_2()" << std::endl;
  }
  ~concrete_class_typeB() {}
};
int main(const int argc, const char **argv) {
  abstract_class *typeA = new concrete_class_typeA();
  abstract_class *typeB = new concrete_class_typeB();

  typeA->template_method();
  typeB->template_method();

  delete typeA;
  delete typeB;

  return 0;
}