#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include "thread_safe_queue.hpp"

const char *RED = "\033[31m";
const char *GREEN = "\033[32m";
const char *RESET = "\033[0m";

void testException()
{
    std::cout << RED << "\n=== Teste de Exceção ===" << RESET << std::endl;

    ThreadSafeQueue<int> queue;

    try
    {
        queue.pop_front(); // Deve lançar exceção pois a fila está vazia
        std::cout << "ERRO: Deveria ter lançado uma exceção!" << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "OK: Exceção capturada corretamente: " << e.what() << std::endl;
    }

    try
    {
        queue.pop_back(); // Deve lançar exceção pois a fila está vazia
        std::cout << "ERRO: Deveria ter lançado uma exceção!" << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "OK: Exceção capturada corretamente: " << e.what() << std::endl;
    }
}

// Teste de Race Condition
void testRaceCondition()
{
    std::cout << RED << "\n=== Teste de Race Condition ===" << RESET << std::endl;

    ThreadSafeQueue<int> queue;
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    const int NUM_THREADS = 5;
    const int ITEMS_PER_THREAD = 100;
    std::atomic<int> totalProduced{0};
    std::atomic<int> totalConsumed{0};

    // Criar threads produtoras
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        producers.emplace_back([&queue, &totalProduced, i]()
                               {
            for (int j = 0; j < ITEMS_PER_THREAD; ++j) {
                if (j % 2 == 0) {
                    queue.push_back(i * 1000 + j);
                } else {
                    queue.push_front(i * 1000 + j);
                }
                totalProduced++;
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            } });
    }

    // Criar threads consumidoras
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        consumers.emplace_back([&queue, &totalConsumed]()
                               {
            while (totalConsumed < NUM_THREADS * ITEMS_PER_THREAD) {
                try {
                    if (rand() % 2 == 0) {
                        queue.pop_front();
                    } else {
                        queue.pop_back();
                    }
                    totalConsumed++;
                    std::this_thread::sleep_for(std::chrono::microseconds(1));
                } catch (const std::runtime_error&) {
                    std::this_thread::sleep_for(std::chrono::microseconds(10));
                }
            } });
    }

    // Join todas as threads
    for (auto &t : producers)
    {
        t.join();
    }
    for (auto &t : consumers)
    {
        t.join();
    }

    std::cout << "Total produzido: " << totalProduced << std::endl;
    std::cout << "Total consumido: " << totalConsumed << std::endl;

    if (totalProduced == totalConsumed)
    {
        std::cout << "OK: Todos os itens foram produzidos e consumidos corretamente!" << std::endl;
    }
    else
    {
        std::cout << "ERRO: Número de itens produzidos e consumidos não correspondem!" << std::endl;
    }
}

void testPush(ThreadSafeQueue<int> &p_queue, int p_value)
{
    p_queue.push_back(p_value);
    std::cout << "Pushed value: " << p_value << std::endl;
}

void testPop(ThreadSafeQueue<int> &p_queue)
{
    try
    {
        int value = p_queue.pop_front();
        std::cout << "Popped value: " << value << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    {
        std::cout << RED << "Test 1" << RESET << std::endl;

        ThreadSafeQueue<int> myQueue;

        std::thread thread1(testPush, std::ref(myQueue), 10);
        std::thread thread2(testPush, std::ref(myQueue), 20);
        std::thread thread3(testPop, std::ref(myQueue));
        std::thread thread4(testPop, std::ref(myQueue));
        std::thread thread5(testPop, std::ref(myQueue));

        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        thread5.join();
    }

    
    testException();
    testRaceCondition();

    return 0;
}
