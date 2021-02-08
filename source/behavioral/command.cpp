#include <iostream>
#include <string>
class command
{
public:
    virtual void execute() = 0;
    virtual ~command() {}
};
class receiver
{
public:
    void action()
    {
        std::cout << "receiver action()" << std::endl;
    }
};
class concrete_command : public command
{
private:
    receiver *m_receiver;

public:
    concrete_command(receiver *receiver) : m_receiver(receiver) {}
    void execute() override
    {
        m_receiver->action();
    }
    ~concrete_command()
    {
        if (m_receiver)
        {
            delete m_receiver;
        }
    }
};

class invoker
{
private:
    command *m_command;

public:
    invoker() {}
    void add_command(command *command)
    {
        m_command = command;
    }
    void execute()
    {
        if (m_command)
        {
            m_command->execute();
        }
    }
};
int main(const int argc, const char **argv)
{
    command *_concrete_command = new concrete_command(new receiver());
    invoker *_invoker = new invoker();

    _invoker->add_command(_concrete_command);
    _invoker->execute();

    delete _invoker;
    delete _concrete_command;
    return 0;
}