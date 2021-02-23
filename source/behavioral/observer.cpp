#include <iostream>
#include <vector>
class subject;
class observer {
public:
  virtual void update(subject *subject) = 0;
  virtual void show_state() = 0;
  virtual ~observer() {}
};

class subject {
private:
  std::vector<observer *> m_observers;

public:
  virtual void attach(observer *observer) { m_observers.push_back(observer); }
  virtual void detach(observer *observer) {
    for (auto iter = m_observers.begin(); iter != m_observers.end(); ++iter) {
      if ((*iter) == observer) {
        m_observers.erase(iter);
        return;
      }
    }
  }
  virtual void notify(subject *subject) {
    for (auto iter = m_observers.begin(); iter != m_observers.end(); ++iter) {
      (*iter)->update(subject);
    }
  }
  virtual int get_state() const = 0;
  virtual void set_state(int state) = 0;
  virtual ~subject() { m_observers.clear(); }
};

class concrete_observer : public observer {
private:
  int m_state;

public:
  void update(subject *subject) override { m_state = subject->get_state(); }
  void show_state() override { std::cout << "state:" << m_state << std::endl; }
};

class concrete_subject : public subject {
private:
  int m_state;

public:
  concrete_subject() {}
  ~concrete_subject() {}
  int get_state() const override { return m_state; }
  void set_state(int state) override {
    m_state = state;
    notify(this);
  }
};
int main(const int argc, const char **argv) {
  observer *_observer = new concrete_observer();
  concrete_subject *_concrete_subject = new concrete_subject();
  _concrete_subject->attach(_observer);

  _concrete_subject->set_state(1024);
  _observer->show_state();

  _concrete_subject->set_state(2048);
  _observer->show_state();

  _concrete_subject->detach(_observer);
  _concrete_subject->set_state(1024);
  _observer->show_state();

  return 0;
}