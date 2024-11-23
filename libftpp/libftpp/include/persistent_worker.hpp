#pragma once

#include <string>
#include <map>
#include <functional>
#include <mutex>
#include "thread.hpp"

class PersistentWorker
{
public:
    PersistentWorker();
    ~PersistentWorker();

    
    void addTask(const std::string &name, const std::function<void()> &jobToExecute);

    void removeTask(const std::string &name);

    // Prevenir cópia :O
    PersistentWorker(const PersistentWorker &) = delete;
    PersistentWorker &operator=(const PersistentWorker &) = delete;

private:
    void workerFunction();

    std::unique_ptr<Thread> worker;
    std::map<std::string, std::function<void()>> tasks;
    std::mutex tasksMutex;
    bool shouldStop;
};