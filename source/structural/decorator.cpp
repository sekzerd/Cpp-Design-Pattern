#include <functional>
#include <iostream>
#include <string>

class component {
public:
    virtual void operation() = 0;

    virtual ~component() {}
};

class concrete_component : public component {
public:
    void operation() override {
        std::cout << "concrete_component operation()" << std::endl;
    }
};

class decorator : public component {
private:
    component *m_component;

public:
    decorator(component *component) : m_component(component) {}

    void operation() override { m_component->operation(); }

    ~decorator() {
        if (m_component) {
            delete m_component;
        }
    }
};

class concrete_decorator_A : public decorator {
private:
    int m_state;

public:
    concrete_decorator_A(component *component) : decorator(component) {}

    void operation() override {
        decorator::operation();
        std::cout << "concrete_decorator_A state:" << m_state << std::endl;
    }

    void add_state(int state) { m_state = state; }
};

class concrete_decorator_B : public decorator {
private:
    std::function<void()> m_function;

public:
    concrete_decorator_B(component *component) : decorator(component) {}

    void operation() override {
        decorator::operation();
        std::cout << "concrete_decorator_B ";
        m_function();
    }

    void add_behavior(std::function<void()> function) { m_function = function; }
};

int main(const int argc, const char **argv) {
    concrete_component *_concrete_component = new concrete_component();

    concrete_decorator_A *_concrete_decorator_A =
            new concrete_decorator_A(_concrete_component);
    _concrete_decorator_A->add_state(1);

    concrete_decorator_B *_concrete_decorator_B =
            new concrete_decorator_B(_concrete_decorator_A);
    _concrete_decorator_B->add_behavior(
            []() { std::cout << "one function" << std::endl; });

    component *component = _concrete_decorator_B;
    component->operation();
    delete component;

    return 0;
}