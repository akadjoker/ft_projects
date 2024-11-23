#include <iostream>
#include <thread>
#include <chrono>

#include "persistent_worker.hpp"
#include "thread_safe_iostream.hpp"

int main()
{
    {
        PersistentWorker worker;

        auto task1 = []()
        {
            threadSafeCout << "Executing Task 1" << std::endl;
        };

        auto task2 = []()
        {
            threadSafeCout << "Executing Task 2" << std::endl;
        };

        worker.addTask("Task1", task1);
        worker.addTask("Task2", task2);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        worker.removeTask("Task1");

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    {
        PersistentWorker worker;

        // Adicionar algumas tarefas
        worker.addTask("Counter1", []()
                       {
        static int count = 0;
        threadSafeCout << "Counter1: " << count++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); });

        worker.addTask("Counter2", []()
                       {
        static int count = 10;
        threadSafeCout << "Counter2: " << count++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); });

        // Deixar executar por um tempo
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // Remover uma tarefa
        worker.removeTask("Counter1");

        // Executar mais um pouco
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return 0;
}
