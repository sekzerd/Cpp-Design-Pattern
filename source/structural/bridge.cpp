#include <iostream>
#include <string>

class implementor {
public:
    virtual void operation_imp() = 0;

    virtual ~implementor() {}
};

class concrete_implemetor_A : public implementor {

public:
    concrete_implemetor_A() {}

    void operation_imp() override {
        std::cout << "concrete_implemetor_A operation_imp()" << std::endl;
    }
};

class concrete_implemetor_B : public implementor {

public:
    concrete_implemetor_B() {}

    void operation_imp() override {
        std::cout << "concrete_implemetor_B operation_imp()" << std::endl;
    }
};

class abstraction {
public:
    virtual void operation() = 0;

    virtual ~abstraction() {}
};

class redefined_abstraction : public abstraction {

private:
    implementor *m_implemetor;

public:
    redefined_abstraction(implementor *implementor_ptr)
            : m_implemetor(implementor_ptr) {}

    void operation() override {
        if (m_implemetor) {
            m_implemetor->operation_imp();
        }
    }

    ~redefined_abstraction() {
        if (m_implemetor) {
            delete m_implemetor;
        }
    }
};

int main(const int argc, const char **argv) {
    abstraction *abstraction_A =
            new redefined_abstraction(new concrete_implemetor_A());
    abstraction *abstraction_B =
            new redefined_abstraction(new concrete_implemetor_B());

    abstraction_A->operation();
    abstraction_B->operation();

    delete abstraction_A;
    delete abstraction_B;

    return 0;
}