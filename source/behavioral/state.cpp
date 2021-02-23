#include <iostream>
enum class SWITCH { ON, OFF };
class state;
class context {
private:
  state *m_state;
  SWITCH m_switch_state;

public:
  context();
  void update_state(state *state);
  void open();
  void shutdown();
  void show_state();
};

class state {
public:
  virtual void on(context &) = 0;
  virtual void off(context &) = 0;
  virtual ~state() {}

protected:
  virtual void change_state(context &) = 0;
};

class state_off : public state {
public:
  state_off();
  void on(context &context) override;
  void off(context &context) override;
  void change_state(context &context) override;
  static state *instance();
  ~state_off();
};

class state_on : public state {
public:
  state_on();
  void on(context &context) override;
  void off(context &context) override;
  void change_state(context &context) override;
  static state *instance();
  ~state_on();
};

state_off::state_off() {}
void state_off::on(context &context) {
  std::cout << "change state on" << std::endl;
  change_state(context);
}
void state_off::off(context &context) {}
void state_off::change_state(context &context) {
  context.update_state(state_on::instance());
}
state *state_off::instance() {
  return new state_off();
  // dynamic state, not static
}
state_off::~state_off() {}

state_on::state_on() {}
void state_on::on(context &context) {}
void state_on::off(context &context) {
  std::cout << "change state off" << std::endl;
  change_state(context);
}
void state_on::change_state(context &context) {
  context.update_state(state_off::instance());
}
state *state_on::instance() {
  return new state_on();
  // dynamic state, not static
}
state_on::~state_on() {}

context::context()
    : m_state(state_off::instance()), m_switch_state(SWITCH::OFF) {}
void context::update_state(state *state) {
  if (m_state) {
    delete m_state;
    m_state = state;
  }
} // for state
void context::open() {
  m_switch_state = SWITCH::ON;
  m_state->on(*this);
}
void context::shutdown() {
  m_switch_state = SWITCH::OFF;
  m_state->off(*this);
}
void context::show_state() {
  switch (m_switch_state) {
  case SWITCH::ON:
    std::cout << "switch is on" << std::endl;
    break;
  case SWITCH::OFF:
    std::cout << "switch is off" << std::endl;
  default:
    break;
  }
}

int main(const int argc, const char **argv) {
  context context;
  context.open();
  context.show_state();
  context.open();
  context.show_state();
  context.shutdown();
  context.show_state();
  context.open();
  context.show_state();
  return 0;
}