#include <iostream>
#include <string>
class memento {
private:
  int m_state;
  int get_state() const { return m_state; }
  void set_state(int state) { m_state = state; }

public:
  ~memento() {}
  friend class originator;
};
class originator : protected memento {
private:
  int m_state;

public:
  originator(int state) : m_state(state) {}
  void set_memento(memento *memento) { m_state = memento->get_state(); }
  memento *create_memento() {
    memento *_memento = new memento();
    _memento->set_state(m_state);
    return _memento;
  }
  void up_state(int state) { m_state = state; }
  void print_state() { std::cout << "state:" << m_state << std::endl; }
};
class caretaker {
private:
  memento *m_memento;

public:
  caretaker() : m_memento(nullptr) {}
  void accept_memento(memento *memento) { m_memento = memento; }
  memento *get_memento() const { return m_memento; }
};
int main(const int argc, const char **argv) {
  originator originator(1);
  caretaker caretaker;

  originator.print_state();

  memento *_memento = originator.create_memento();
  caretaker.accept_memento(_memento);
  originator.up_state(100);

  originator.print_state();

  originator.set_memento(caretaker.get_memento());

  originator.print_state();

  return 0;
}