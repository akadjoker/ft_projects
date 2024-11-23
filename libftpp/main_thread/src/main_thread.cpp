#include <iostream>
#include <chrono>
#include "thread.hpp"
#include "thread_safe_iostream.hpp"

const char *RED = "\033[31m";
const char *GREEN = "\033[32m";
const char *RESET = "\033[0m";

void myFunction1()
{
    for (int i = 0; i < 5; ++i)
    {
        threadSafeCout << "Hello from Function1, iteration " << i << std::endl;
    }
}

void myFunction2()
{
    for (int i = 0; i < 5; ++i)
    {
        threadSafeCout << "Hello from Function2, iteration " << i << std::endl;
    }
}

int main()
{
    {
        std::cout << RED << "Test 1" << RESET << std::endl;

        Thread thread1("Thread1", myFunction1);
        Thread thread2("Thread2", myFunction2);

        thread1.start();
        thread2.start();

        thread1.stop();
        thread2.stop();
    }

    {
        std::cout << RED << "Test 2" << RESET << std::endl;
        Thread worker1("Worker1", []()
                       {
        for (int i = 0; i < 5; ++i) {
            threadSafeCout << "Working... count: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } });

        Thread worker2("Worker2", []()
                       {
        for (int i = 0; i < 3; ++i) {
            threadSafeCout << "Processing... iteration: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        } });

        // Iniciar as threads
        worker1.start();
        worker2.start();

        // Fazer algo na thread principal
        threadSafeCout.setPrefix("[Main] ");
        threadSafeCout << "Main thread working..." << std::endl;

        // Parar as threads
        worker1.stop();
        worker2.stop();
    }

    return 0;
}
