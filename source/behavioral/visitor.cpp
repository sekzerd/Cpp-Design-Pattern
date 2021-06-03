#include <iostream>
#include <vector>

class visitor;

class element {
public:
    virtual void accept(visitor *visitor) = 0;

    virtual ~element() {}
};

class visitor {
public:
    virtual void visit_elementA(element *element) = 0;

    virtual void visit_elementB(element *element) = 0;

    virtual ~visitor() {}
};

class elementA : public element {
public:
    elementA() {}

    void accept(visitor *visitor) override { visitor->visit_elementA(this); }

    void operationA() { std::cout << "elementA "; }

    ~elementA() {}
};

class elementB : public element {
public:
    elementB() {}

    void accept(visitor *visitor) override { visitor->visit_elementB(this); }

    void operationB() { std::cout << "elementB "; }

    ~elementB() {}
};

class concrete_visit_elementA : public visitor {
public:
    concrete_visit_elementA() {}

    void visit_elementA(element *element) override {
        dynamic_cast<elementA *>(element)->operationA();
        std::cout << "visited by concrete_visit_elementA" << std::endl;
    }

    void visit_elementB(element *element) override {
        dynamic_cast<elementB *>(element)->operationB();
        std::cout << "visited by concrete_visit_elementA" << std::endl;
    }

    ~concrete_visit_elementA() {}
};

class concrete_visit_elementB : public visitor {
public:
    concrete_visit_elementB() {}

    void visit_elementA(element *element) override {
        dynamic_cast<elementA *>(element)->operationA();
        std::cout << "visited by concrete_visit_elementB" << std::endl;
    }

    void visit_elementB(element *element) override {
        dynamic_cast<elementB *>(element)->operationB();
        std::cout << "visited by concrete_visit_elementB" << std::endl;
    }

    ~concrete_visit_elementB() {}
};

class object_structre {
private:
    std::vector<element *> m_elements;

public:
    object_structre() {
        m_elements.push_back(new elementA());
        m_elements.push_back(new elementB());
    }

    void accept(visitor *visitor) {
        for (auto iter = m_elements.begin(); iter != m_elements.end(); ++iter) {
            (*iter)->accept(visitor);
        }
    }
};

int main(const int argc, const char **argv) {
    concrete_visit_elementA *_concrete_visit_elementA =
            new concrete_visit_elementA();
    concrete_visit_elementB *_concrete_visit_elementB =
            new concrete_visit_elementB();

    object_structre object_structre;
    object_structre.accept(_concrete_visit_elementA);
    object_structre.accept(_concrete_visit_elementB);

    delete _concrete_visit_elementA;
    delete _concrete_visit_elementB;

    return 0;
}