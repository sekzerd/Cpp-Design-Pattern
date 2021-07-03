#include <iostream>
#include <vector>

class aggregate;

class iterator {
public:
    iterator() {}

    virtual int first() = 0;

    virtual int end() = 0;

    virtual void inverse() = 0;

    virtual void next() = 0;

    virtual void reset_inverse() = 0;

    virtual bool is_start() = 0;

    virtual bool is_end() = 0;

    virtual int current_item() = 0;

    virtual ~iterator() {}
};

class aggregate {
public:
    aggregate() {}

    virtual void push(const int i) = 0;

    virtual iterator *get_iterator() = 0;

    virtual  ~aggregate() {}
};

class aggregate_vector;

class iterator_vector : public iterator {
private:
    int m_cursor;
    std::vector<int> *m_target_vector;
public:
    iterator_vector(aggregate_vector *target);

    int first();

    int end();

    void next() override;

    void inverse() override;

    void reset_inverse() override;

    bool is_start() override;


    bool is_end() override;

    int current_item() override;

    ~iterator_vector();
};

class aggregate_vector : public aggregate {
    friend class iterator_vector;

private:
    std::vector<int> m_vector;
public:
    aggregate_vector() {}

    void push(const int i) override {
        m_vector.push_back(i);
    }

    iterator *get_iterator() {
        return new iterator_vector(this);
    }


    ~aggregate_vector() {}

};

iterator_vector::iterator_vector(aggregate_vector *target) {
    m_target_vector = &(target->m_vector);
    m_cursor = 0;
}

int iterator_vector::first() {
    if (m_target_vector->size() != 0) {
        return m_target_vector->front();
    }
    return 0;//default 0
}

int iterator_vector::end() {
    if (m_target_vector->size() != 0) {
        return m_target_vector->back();
    }
    return 0;//default 0
}

void iterator_vector::next() {
    m_cursor++;
}

void iterator_vector::inverse() {
    if (m_cursor != -1) {
        m_cursor--;
    }
}

void iterator_vector::reset_inverse() {
    m_cursor = m_target_vector->size()-1;
}

bool iterator_vector::is_start() {
    return m_cursor == -1;
}


bool iterator_vector::is_end() {
    return m_cursor == (m_target_vector->size());
}

int iterator_vector::current_item() {
    return m_target_vector->at(m_cursor);
}

iterator_vector::~iterator_vector() {}

int main(const int argc, const char **argv) {

    aggregate_vector aggregateVector;

    for (size_t i = 0; i < 10; ++i) {
        aggregateVector.push(i);
    }

    iterator *_iterator = aggregateVector.get_iterator();

    std::cout << "end item:" << _iterator->end() << std::endl;
    for (; !_iterator->is_end(); _iterator->next()) {
        std::cout << "item:" << _iterator->current_item() << std::endl;
    }

    std::cout << "first item:" << _iterator->first() << std::endl;
    for ( _iterator->reset_inverse(); !_iterator->is_start(); _iterator->inverse()) {
        std::cout << "inverse item:" << _iterator->current_item() << std::endl;
    }

    delete _iterator;

    return 0;
}