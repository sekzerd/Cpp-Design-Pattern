#include <iostream>
#include <string>

class abstract_product_A {
public:
    virtual ~abstract_product_A() {}

    virtual std::string get_name() = 0;
};

class abstract_product_B {
public:
    virtual ~abstract_product_B() {}

    virtual std::string get_name() = 0;
};

class product_A1 : public abstract_product_A {
public:
    ~product_A1() {}

    std::string get_name() override { return std::string("product_A1"); }
};

class product_A2 : public abstract_product_A {
public:
    ~product_A2() {}

    std::string get_name() override { return std::string("product_A2"); }
};

class product_B1 : public abstract_product_B {
public:
    ~product_B1() {}

    std::string get_name() override { return std::string("product_B1"); }
};

class product_B2 : public abstract_product_B {
public:
    ~product_B2() {}

    std::string get_name() override { return std::string("product_B2"); }
};

class abstract_factory {
public:
    virtual abstract_product_A *create_product_A() = 0;

    virtual abstract_product_B *create_product_B() = 0;

    virtual ~abstract_factory() {}
};

class concrete_factory_1 : public abstract_factory {
public:
    abstract_product_A *create_product_A() override { return new product_A1(); }

    abstract_product_B *create_product_B() override { return new product_B1(); }
};

class concrete_factory_2 : public abstract_factory {
public:
    abstract_product_A *create_product_A() override { return new product_A2(); }

    abstract_product_B *create_product_B() override { return new product_B2(); }
};

int main(const int argc, const char **argv) {
    abstract_factory *factory1 = new concrete_factory_1();
    abstract_factory *factory2 = new concrete_factory_2();
    abstract_product_A *productA1 = factory1->create_product_A();
    abstract_product_A *productA2 = factory2->create_product_A();
    abstract_product_B *productB1 = factory1->create_product_B();
    abstract_product_B *productB2 = factory2->create_product_B();
    std::cout << productA1->get_name() << std::endl;
    std::cout << productA2->get_name() << std::endl;
    std::cout << productB1->get_name() << std::endl;
    std::cout << productB2->get_name() << std::endl;

    delete productA1;
    delete productA2;
    delete productB1;
    delete productB2;
    delete factory1;
    delete factory2;

    return 0;
}