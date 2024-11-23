#pragma once

#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <sstream>




// O mutex estático (static std::mutex s_mutex) é compartilhado entre todas as threads, garantimos sincronização global para a escrita
// O buffer thread_local permite que cada thread acumula a mensagem independentemente "pipex :D"
// O prefixo thread_local mantém um prefixo único por thread
// O lock acontece apenas no momento do flush (endl), minimizando o tempo de lock e maximizando a performance :)

class ThreadSafeIOStream
{
public:

    ThreadSafeIOStream() = default;
    ~ThreadSafeIOStream() = default;

    void setPrefix(const std::string &prefix);

    //  operador << para diferentes tipos de dados
    template <typename T>
    ThreadSafeIOStream &operator<<(const T &data)
    {
        buffer << data;
        return *this;
    }

    //  operador << para std::endl
    ThreadSafeIOStream &operator<<(std::ostream &(*manip)(std::ostream &))
    {
        buffer << manip;
        if (manip == static_cast<std::ostream &(*)(std::ostream &)>(std::endl))
        {
            // Lock global para a escrita
            std::lock_guard<std::mutex> lock(s_mutex);
            std::cout << threadPrefix << buffer.str();
            buffer.str("");
            buffer.clear();
        }
        return *this;
    }

private:
    static std::mutex s_mutex;                    // Mutex estático compartilhado
    thread_local static std::string threadPrefix; // Prefixo único por thread
    thread_local static std::stringstream buffer; // Buffer por thread
};

// Instância global GLOBALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLl
extern thread_local ThreadSafeIOStream threadSafeCout;

