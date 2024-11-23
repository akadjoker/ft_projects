#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "thread.hpp"
#include "thread_safe_queue.hpp"

class IJob
{
public:
    virtual void execute() = 0;
    virtual ~IJob() = default;
};

class WorkerPool
{
public:
    WorkerPool(size_t numThreads);
    ~WorkerPool();

    void addJob(const std::function<void()> &jobToExecute);

private:

    void workerThread();


    std::queue<std::function<void()>> jobQueue;


    std::mutex queueMutex;
    std::condition_variable condition;


    std::atomic<bool> stop;

    std::vector<std::thread> workers;
};