#include <iostream>
#include <list>
#include <string>
class component
{
public:
    virtual void operation() = 0;
    virtual void add_component(component *component) {}
    virtual void remove_component(component *component) {}
    virtual component *get_child(const int pos)
    {
        return nullptr;
    }
    virtual ~component() {}
};

class leaf : public component
{
private:
    int m_id;

public:
    leaf(int id) : m_id(id) {}
    void operation() override
    {
        std::cout << "leaf id " << m_id << " operation()" << std::endl;
    }
    ~leaf() {}
};
class composite : public component
{
private:
    std::list<component *> m_childs;

public:
    composite() : m_childs() {}
    void operation() override
    {
        for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter)
        {
            (*iter)->operation();
        }
    }
    void add_component(component *component) override
    {
        m_childs.push_back(component);
    }
    void remove_component(component *_component) override
    {
        for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter)
        {
            if ((*iter) == _component)
            {
                component *subroot = (*iter);
                delete subroot;
                m_childs.erase(iter);
            }
        }
    }
    component *get_child(const int pos) override
    {
        int i = 0;
        for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter)
        {
            i++;
            if (i == pos)
            {
                return *iter;
            }
        }
        return nullptr;
    }
    ~composite()
    {
        for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter)
        {
            delete (*iter);
        }
        m_childs.clear();
    }
};
int main(const int argc, const char **argv)
{
    component *root = new composite();
    component *first_subnode = new composite();
    component *second_subnode = new composite();

    second_subnode->add_component(new leaf(21));

    first_subnode->add_component(new leaf(11));
    first_subnode->add_component(second_subnode);

    root->add_component(new leaf(1));   // id 1
    root->add_component(new leaf(2));   // id 2
    root->add_component(new leaf(3));   // id 3
    root->add_component(first_subnode); // id 4
    root->add_component(new leaf(4));   // id 5

    component *target_node = root->get_child(4);
    target_node->operation(); //access leaf 11,21;

    root->remove_component(first_subnode);

    root->operation(); //access leaf 1,2,3,4

    delete root;
    return 0;
}