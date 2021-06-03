#include <iostream>
#include <string>

class product {
public:
    virtual ~product() {}

    virtual std::string get_name() = 0;
};

class concreate_productA : public product {

public:
    std::string get_name() override { return std::string("productA"); }
};

class concreate_productB : public product {
public:
    std::string get_name() override { return std::string("productB"); }
};

class creator {
public:
    virtual ~creator() {}

    virtual product *create_productA() = 0;

    virtual product *create_productB() = 0;
};

class concreate_creator : public creator {
public:
    product *create_productA() override { return new concreate_productA(); }

    product *create_productB() override { return new concreate_productB(); }
};

int main(const int argc, const char **) {
    creator *concreator_creator = new concreate_creator();
    product *productA = concreator_creator->create_productA();
    product *productB = concreator_creator->create_productB();
    std::cout << productA->get_name() << std::endl;
    std::cout << productB->get_name() << std::endl;

    delete productA;
    delete productB;
    delete concreator_creator;

    return 0;
}