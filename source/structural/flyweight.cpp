#include <iostream>
#include <vector>
class flyweight
{
public:
    virtual void operation() = 0;
    virtual ~flyweight() {}
};

class concrete_flyweight : public flyweight
{
private:
    int m_state;

public:
    concrete_flyweight(const int state) : m_state(state) {}
    void operation() override
    {
        std::cout << "concrete_flyweight state:" << m_state << std::endl;
    }
};
class unshared_concrete_flyweight : public flyweight
{
private:
    int m_state;

public:
    unshared_concrete_flyweight(const int state) : m_state(state) {}
    void operation() override
    {
        std::cout << "unshared_concrete_flyweight state:" << m_state << std::endl;
    }
};
class flyweight_factory
{
private:
    std::vector<flyweight *> m_flyweights;

public:
    flyweight_factory() : m_flyweights() {}
    ~flyweight_factory() {}
    flyweight *get_flyweight(const int key)
    {
        if (key <= m_flyweights.size() && (m_flyweights.size() != 0))
        {
            return m_flyweights[key];
        }
        else
        {
            m_flyweights.push_back(new concrete_flyweight(key));
            return m_flyweights.back();
        }
    }
};
int main(const int argc, const char **argv)
{
    flyweight_factory *_flyweight_factory = new flyweight_factory();
    _flyweight_factory->get_flyweight(1)->operation();
    _flyweight_factory->get_flyweight(2)->operation();
    _flyweight_factory->get_flyweight(3)->operation();
    delete _flyweight_factory;
    return 0;
}