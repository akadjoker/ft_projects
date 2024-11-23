#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include "thread_safe_iostream.hpp"

const char* RED = "\033[31m";
const char* GREEN = "\033[32m";
const char* RESET = "\033[0m";

const int NUM_THREADS = 5;

void worker(const std::string &threadName)
{
    // Cada thread usa o mesmo threadSafeCout mas com seu próprio prefix
    threadSafeCout.setPrefix(threadName);

    // Cada thread vai escrever várias mensagens
    for (int i = 0; i < NUM_THREADS; i++)
    {

         threadSafeCout<<GREEN << "  Count: " << i << " | Message from " << threadName <<RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    }
}
void printNumbers(const std::string &p_prefix)
{
    threadSafeCout.setPrefix(p_prefix);
    for (int i = 1; i <= 5; ++i)
    {
        threadSafeCout << "Number: " << i << std::endl;
    }
}

int main()
{
    {

        std::cout<<RED << "Test 1" <<  RESET<<std::endl;
        threadSafeCout.setPrefix("Test");
        threadSafeCout << "Hello World" << std::endl;

        std::thread t1([]()
                       {
        threadSafeCout.setPrefix("Thread1");
        threadSafeCout << "Message from thread 1" << std::endl; });

        t1.join();
    }
    {
        std::cout <<  RED << "Test 2" << RESET << std::endl;
        std::string prefix1 = "[Thread 1] ";
        std::string prefix2 = "[Thread 2] ";

        std::thread thread1(printNumbers, prefix1);
        std::thread thread2(printNumbers, prefix2);

        thread1.join();
        thread2.join();
    }

    {
        std::cout <<  RED << "Test 3" << RESET << std::endl;
        std::vector<std::thread> threads;

        // Thread principal
        threadSafeCout.setPrefix("Main");

        // Criar cada thread com um nome único
        for (int i = 0; i < NUM_THREADS; ++i)
        {
            std::string threadName = "Worker" + std::to_string(i);
            threads.emplace_back(worker, threadName);
        }

        // Mensagens do thread principal
        for (int i = 0; i < 5; ++i)
        {
            threadSafeCout << "Main thread message: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }

        // Esperar todos os threads terminarem
        for (auto &t : threads)
        {
            t.join();
        }
    }

    return 0;
}
