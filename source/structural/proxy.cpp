#include <iostream>
#include <string>

class subject {
public:
    virtual void request() = 0;

    virtual ~subject() {}
};

class realsubject : public subject {
public:
    void request() override { std::cout << "realsubject request()" << std::endl; }
};

class proxy : public subject {
private:
    subject *m_subject;

public:
    proxy() : m_subject(nullptr) {}

    void construct_subject() {
        if (!m_subject) {
            m_subject = new realsubject();
        }
    }

    void destruct_subject() {
        if (m_subject) {
            delete m_subject;
        }
    }

    void request() override {
        if (m_subject) {
            m_subject->request();
        }
    }

    ~proxy() { destruct_subject(); }
};

int main(const int argc, const char **argv) {
    proxy *_proxy = new proxy();
    _proxy->construct_subject();
    _proxy->request();

    delete _proxy;

    return 0;
}