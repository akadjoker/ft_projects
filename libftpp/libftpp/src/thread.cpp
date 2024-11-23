#include "thread.hpp"

Thread::Thread(const std::string &name, std::function<void()> functToExecute)
    : threadName(name), threadFunction([this, functToExecute]()
                                       {
        // Configura o prefixo para ThreadSafeIOStream antes de executar
        threadSafeCout.setPrefix("[" + threadName + "] ");
        functToExecute(); }),
      isRunning(false)
{
}

Thread::~Thread()
{
    if (isRunning)
    {
        stop();
    }
}

void Thread::start()
{
    if (!isRunning)
    {
        isRunning = true;
        thread = std::thread(threadFunction);
    }
}

void Thread::stop()
{
    if (isRunning)
    {
        if (thread.joinable())
        {
            thread.join();
        }
        isRunning = false;
    }
}

//  construtor de movimento
Thread::Thread(Thread &&other) noexcept
    : threadName(std::move(other.threadName)), threadFunction(std::move(other.threadFunction)), thread(std::move(other.thread)), isRunning(other.isRunning)
{
    other.isRunning = false;
}

//  operador de atribuição por movimento
Thread &Thread::operator=(Thread &&other) noexcept
{
    if (this != &other)
    {
        if (isRunning)
        {
            stop();
        }
        threadName = std::move(other.threadName);
        threadFunction = std::move(other.threadFunction);
        thread = std::move(other.thread);
        isRunning = other.isRunning;
        other.isRunning = false;
    }
    return *this;
}