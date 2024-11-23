#include <iostream>
#include <thread>
#include <chrono>

#include "worker_pool.hpp"
#include "thread_safe_iostream.hpp"

int main()
{
    {
        WorkerPool pool(4);

        auto job = []()
        {
            threadSafeCout << "Executing job on thread: " << std::this_thread::get_id() << std::endl;
        };

        for (int i = 0; i < 1000; ++i)
        {
            pool.addJob(job);
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    {

        WorkerPool pool(4);

        // Adicionar alguns jobs
        for (int i = 0; i < 10; ++i)
        {
            pool.addJob([i]()
                        {
            threadSafeCout << "Executing job " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); });
        }

        std::this_thread::sleep_for(std::chrono::seconds(6));
    }
    return 0;
}
