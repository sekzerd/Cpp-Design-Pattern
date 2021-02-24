#include <iostream>
#include <string>
class prototype {
public:
  virtual prototype *clone() const = 0;
  virtual void do_something() const = 0;
  virtual ~prototype() {}
};
class concrete_prototype1 : public prototype {
private:
  std::string m_data;

public:
  concrete_prototype1() : m_data(std::string("concrete_prototype1")) {}
  void do_something() const override { std::cout << m_data << std::endl; }
  prototype *clone() const override { return new concrete_prototype1(); }
};
class concrete_prototype2 : public prototype {
private:
  std::string m_data;

public:
  void do_something() const override { std::cout << m_data << std::endl; }
  concrete_prototype2() : m_data(std::string("concrete_prototype2")) {}
  prototype *clone() const override { return new concrete_prototype2(); }
};
class client {
private:
  prototype *prototype_list[2];

public:
  client() {
    prototype_list[0] = new concrete_prototype1();
    prototype_list[1] = new concrete_prototype2();
  }
  prototype *clone_concrete_prototype1() { return prototype_list[0]->clone(); }
  prototype *clone_concrete_prototype2() { return prototype_list[1]->clone(); }
  virtual ~client() {}
};
int main(const int agrc, const char **argv) {
  client client_instance;
  prototype *prototype_type1 = client_instance.clone_concrete_prototype1();
  prototype *prototype_type2 = client_instance.clone_concrete_prototype2();
  prototype_type1->do_something();
  prototype_type2->do_something();

  delete prototype_type2;
  delete prototype_type1;

  return 0;
}