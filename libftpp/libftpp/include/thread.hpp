#pragma once

#include <string>
#include <functional>
#include <thread>
#include "thread_safe_iostream.hpp"

class Thread
{
public:

    Thread(const std::string &name, std::function<void()> functToExecute);

    // Destrutor (garantimos que a thread seja parada)
    ~Thread();

    // Inicia a execução da thread
    void start();

    // Para a execução da thread
    void stop();

    // Não permitir cópia
    Thread(const Thread &) = delete;
    Thread &operator=(const Thread &) = delete;

    // Permitir movimento
    Thread(Thread &&) noexcept;
    Thread &operator=(Thread &&) noexcept;

    // Getter para o nome da thread
    const std::string &getName() const { return threadName; }

private:
    std::string threadName;               // Nome da thread
    std::function<void()> threadFunction; // Função a ser executada
    std::thread thread;                   // A thread em si
    bool isRunning;                       // Estado da thread
};