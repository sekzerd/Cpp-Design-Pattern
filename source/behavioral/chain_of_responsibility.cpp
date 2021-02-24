#include <iostream>
#include <string>
enum class request_type { TYPE_A, TYPE_B, NONE };
class request {
private:
  request_type m_type;
  std::string m_content;

public:
  request(const request_type type, const std::string &content)
      : m_type(type), m_content(content) {}
  request_type type() const { return m_type; }
  std::string get_content() const { return m_content; }
};
class handler {
public:
  virtual void handle_request(request *request) = 0;
  virtual void add_next_handler(handler *handler) {}
  virtual ~handler() {}
};
class concrete_handler_A : public handler {
private:
  handler *m_next_handler;

public:
  concrete_handler_A() : m_next_handler(nullptr) {}
  void handle_request(request *_request) override {
    if (_request->type() == request_type::TYPE_A) {
      std::cout << "concrete_handler_A handle request" << std::endl;
      std::cout << "request content:" << _request->get_content() << std::endl;
    } else {
      if (m_next_handler) {
        m_next_handler->handle_request(_request);
      }
    }
  }
  void add_next_handler(handler *handler) override { m_next_handler = handler; }
};
class concrete_handler_B : public handler {

private:
  handler *m_next_handler;

public:
  concrete_handler_B() : m_next_handler(nullptr) {}
  void handle_request(request *_request) override {
    if (_request->type() == request_type::TYPE_B) {
      std::cout << "concrete_handler_B handle request" << std::endl;
      std::cout << "request content:" << _request->get_content() << std::endl;
    } else {
      if (m_next_handler) {
        m_next_handler->handle_request(_request);
      }
    }
  }
  void add_next_handler(handler *handler) override { m_next_handler = handler; }
};
class none_handler : public handler {
public:
  none_handler() {}
  void handle_request(request *_request) override {
    std::cout << "none_handler handle request" << std::endl;
    std::cout << "request content:" << _request->get_content() << std::endl;
  }
};

int main(const int argc, const char **argv) {
  handler *_concrete_handler_A = new concrete_handler_A();
  handler *_concrete_handler_B = new concrete_handler_B();
  handler *_none_handler = new none_handler();

  _concrete_handler_A->add_next_handler(_concrete_handler_B);
  _concrete_handler_B->add_next_handler(_none_handler);

  request *request_A =
      new request(request_type::TYPE_A, std::string("request_A"));
  request *request_B =
      new request(request_type::TYPE_B, std::string("request_B"));
  request *request_none =
      new request(request_type::NONE, std::string("request_none"));

  _concrete_handler_A->handle_request(request_none);
  _concrete_handler_A->handle_request(request_B);
  _concrete_handler_A->handle_request(request_A);

  delete _none_handler;
  delete _concrete_handler_B;
  delete _concrete_handler_A;

  return 0;
}