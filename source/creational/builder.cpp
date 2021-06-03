#include <iostream>
#include <string>

class product {
private:
    std::string m_data;

public:
    void build_part1(const std::string &part) { m_data.append(part); }

    void build_part2(const std::string &part) { m_data.append(part); }

    void build_part3(const std::string &part) { m_data.append(part); }

    void do_something() { std::cout << m_data << std::endl; }

    product() {}

    virtual ~product() {}
};

class builder {
public:
    virtual void build_part1() = 0;

    virtual void build_part2() = 0;

    virtual void build_part3() = 0;

    virtual product get_result() = 0;

    virtual ~builder() {}
};

class concrete_builder1 : public builder {
private:
    product m_product;

public:
    concrete_builder1() : m_product() {}

    void build_part1() override {
        m_product.build_part1(std::string("%concrete1_part1"));
    }

    void build_part2() override {
        m_product.build_part1(std::string("%concrete1_part2"));
    }

    void build_part3() override {
        m_product.build_part1(std::string("%concrete1_part3"));
    }

    product get_result() override { return m_product; }
};

class concrete_builder2 : public builder {
private:
    product m_product;

public:
    concrete_builder2() : m_product() {}

    void build_part1() override {
        m_product.build_part1(std::string("%concrete2_part1"));
    }

    void build_part2() override {
        m_product.build_part1(std::string("%concrete2_part2"));
    }

    void build_part3() override {
        m_product.build_part1(std::string("%concrete2_part3"));
    }

    product get_result() override { return m_product; }
};

class director {
private:
    builder *m_builder_list[2];

public:
    director() {}

    void construct() {
        m_builder_list[0] = new concrete_builder1();
        m_builder_list[1] = new concrete_builder2();
        m_builder_list[0]->build_part1();
        m_builder_list[0]->build_part2();
        m_builder_list[0]->build_part3();
        m_builder_list[1]->build_part1();
        m_builder_list[1]->build_part2();
        m_builder_list[1]->build_part3();
    }

    product get_concrete1() const { return m_builder_list[0]->get_result(); }

    product get_concrete2() const { return m_builder_list[1]->get_result(); }

    void destrcut() {
        if (m_builder_list[0]) {
            delete m_builder_list[0];
        }
        if (m_builder_list[1]) {
            delete m_builder_list[1];
        }
    }

    ~director() { destrcut(); }
};

int main(const int argc, const char **argv) {
    director director_instance;
    director_instance.construct();
    product product1 = director_instance.get_concrete1();
    product product2 = director_instance.get_concrete2();
    product1.do_something();
    product2.do_something();

    return 0;
}
