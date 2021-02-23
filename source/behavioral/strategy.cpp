#include <iostream>

class strategy {
public:
  virtual int compute(int, int) = 0;
  ~strategy() {}
};
class method_add : public strategy {
public:
  int compute(int a, int b) override { return a + b; }
};
class method_sub : public strategy {
public:
  int compute(int a, int b) override { return a - b; }
};
class method_mul : public strategy {
public:
  int compute(int a, int b) override { return a * b; }
};
class context {
private:
  int m_num_A;
  int m_num_B;
  int m_result;
  strategy *m_strategy;

public:
  context(int a, int b) : m_num_A(a), m_num_B(b) {}
  void select_method(strategy *strategy) { m_strategy = strategy; }
  void compute() {
    if (m_strategy) {
      m_result = m_strategy->compute(m_num_A, m_num_B);
    }
  }
  void print_result() { std::cout << "result:" << m_result << std::endl; }
};

int main(const int argc, const char **argv) {
  strategy *add_strategy = new method_add();
  strategy *sub_strategy = new method_sub();
  strategy *mul_strategy = new method_mul();

  context _context(3, 2);
  _context.select_method(add_strategy);
  _context.compute();
  _context.print_result();

  _context.select_method(sub_strategy);
  _context.compute();
  _context.print_result();

  _context.select_method(mul_strategy);
  _context.compute();
  _context.print_result();

  _context.select_method(add_strategy);
  _context.compute();
  _context.print_result();

  delete add_strategy;
  delete sub_strategy;
  delete mul_strategy;

  return 0;
}