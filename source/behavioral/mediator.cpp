
#include <iostream>
#include <string>
#include <vector>

class colleague;

class mediator {
public:
    virtual void set(const std::string &str) = 0;

    virtual void add(colleague *colleague) = 0;

    virtual ~mediator() {}
};

class colleague {
private:
    mediator *m_mediator;
    std::string m_data;
    int m_id;

public:
    colleague(const int id, mediator *mediator)
            : m_mediator(mediator), m_id(id) {}

    void send_by_mediator(const std::string &str) {
        m_data = str;
        m_mediator->set(str);
    }

    void accept_from_mediator(const std::string &str) {
        m_data = str;
    } // for mediator
    std::string get() const { return m_data; }

    int get_id() const { return m_id; }
};

class public_mediator : public mediator {
private:
    std::vector<colleague *> m_colleagues;

public:
    public_mediator() {}

    void set(const std::string &str) override {
        for (auto iter = m_colleagues.begin(); iter != m_colleagues.end(); ++iter) {
            (*iter)->accept_from_mediator(str);
        }
    }

    void add(colleague *colleague) override { m_colleagues.push_back(colleague); }

    ~public_mediator() {}
};

int main(const int argc, const char **argv) {
    mediator *_public_mediator = new public_mediator();
    std::vector<colleague *> colleagues;
    for (auto i = 0; i < 10; ++i) {
        colleague *_colleague = new colleague(i, _public_mediator);
        _public_mediator->add(_colleague);
        colleagues.push_back(_colleague);
    }

    std::cout << "info hello" << std::endl;
    colleagues.front()->send_by_mediator(std::string("hello"));
    for (auto iter = colleagues.begin(); iter != colleagues.end(); ++iter) {
        std::cout << "id:" << (*iter)->get_id() << "\t";
        std::cout << "str:" << (*iter)->get() << std::endl;
    }

    std::cout << "info world" << std::endl;
    colleagues.back()->send_by_mediator(std::string("world"));
    for (auto iter = colleagues.begin(); iter != colleagues.end(); ++iter) {
        std::cout << "id:" << (*iter)->get_id() << "\t";
        std::cout << "str:" << (*iter)->get() << std::endl;
    }

    return 0;
}