#include <iostream>
#include <string>
#include <vector>

enum class OP {
    ADD,
    SUB,
    EQ
};

class context {
private:
    context *m_next_cxt;
    OP m_op;
    int m_number;
public:
    context(context *next_cxt, const int n, const OP op) : m_next_cxt(next_cxt), m_number(n),
                                                           m_op(op) {}

    context *get_next_cxt() const { return m_next_cxt; }

    OP get_op() const { return m_op; }

    int get_number() const { return m_number; }
};

class abstract_expression {
public:
    abstract_expression() {}

    virtual int interpret(context *cxt) = 0;

    virtual ~abstract_expression() {}
};

class add_expression : public abstract_expression {
public:
    add_expression() {}

    int interpret(context *cxt) override {
        return cxt->get_number();
    }

    ~add_expression() {}
};

class sub_expression : public abstract_expression {
public:
    sub_expression() {}

    int interpret(context *cxt) override {
        return -(cxt->get_number());
    }

    ~sub_expression() {}
};

class eq_expression : public abstract_expression {
public:
    eq_expression() {}

    int interpret(context *cxt) override {
        return 0;
    }

    ~eq_expression() {}
};

context *build_context() {
    //-2+7+1-3=0
    context *eq = new context(nullptr, 0, OP::EQ);//=0
    context *sub3 = new context(eq, 3, OP::SUB);//-3
    context *add1 = new context(sub3, 1, OP::ADD);//+1
    context *add7 = new context(add1, 7, OP::ADD);//+7
    context *sub2 = new context(add7, 2, OP::SUB);//-2
    return sub2;
}

void destroy_context(context *root) {
    std::vector<context *> todo_list;
    while (root != nullptr) {
        todo_list.push_back(root);
        root = root->get_next_cxt();
    }
    for (size_t i = 0; i < todo_list.size(); ++i) {
        delete todo_list[i];
    }
}

class client {
private:
    context *root;
public:
    client(context *cxt) : root(cxt) {
    }

    int result() {
        std::vector<abstract_expression *> expressions;
        auto cursor = root;
        while (cursor != nullptr) {
            switch (cursor->get_op()) {
                case OP::ADD:
                    expressions.push_back(new add_expression);
                    break;
                case OP::SUB:
                    expressions.push_back(new sub_expression);
                    break;
                case OP::EQ:
                    expressions.push_back(new eq_expression);
                    break;

            }

            cursor = cursor->get_next_cxt();
        }
        int result = 0;
        cursor = root;
        //compute the result
        for (size_t i = 0; i < expressions.size(); ++i) {
            result += expressions[i]->interpret(cursor);
            cursor = cursor->get_next_cxt();
        }
        // destroy the expressions
        for (size_t i = 0; i < expressions.size(); ++i) {
            delete expressions[i];
        }
        // destroy the context
        destroy_context(root);

        return result;
    }

    ~client() {}
};

int main(const int argc, const char **argv) {
    client _client(build_context());
    std::cout << "result:" << _client.result() << std::endl;

    return 0;
}