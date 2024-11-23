#include "worker_pool.hpp"
#include "worker_pool.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>

WorkerPool::WorkerPool(size_t numThreads) : stop(false)
{

    for (size_t i = 0; i < numThreads; ++i)
    {
        workers.emplace_back(&WorkerPool::workerThread, this);
    }
}

WorkerPool::~WorkerPool()
{

    stop = true;
    condition.notify_all();

    for (auto &worker : workers)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}

void WorkerPool::addJob(const std::function<void()> &jobToExecute)
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        jobQueue.push(jobToExecute);
    }
    condition.notify_one();
}

void WorkerPool::workerThread()
{
    while (!stop)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            condition.wait(lock, [this]
                           { return !jobQueue.empty() || stop; });

            if (stop && jobQueue.empty())
            {
                return;
            }

            job = std::move(jobQueue.front());
            jobQueue.pop();
        }

        job();
    }
}
