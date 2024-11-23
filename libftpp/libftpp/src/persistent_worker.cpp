#include "persistent_worker.hpp"
#include <thread>

PersistentWorker::PersistentWorker()
    : shouldStop(false)
{
    worker = std::make_unique<Thread>(
        "PersistentWorker",
        [this]()
        { this->workerFunction(); });
    worker->start();
}

PersistentWorker::~PersistentWorker()
{
    shouldStop = true;
    worker.reset();
}

void PersistentWorker::addTask(const std::string &name, const std::function<void()> &jobToExecute)
{
    std::lock_guard<std::mutex> lock(tasksMutex);
    tasks[name] = jobToExecute;
}

void PersistentWorker::removeTask(const std::string &name)
{
    std::lock_guard<std::mutex> lock(tasksMutex);
    tasks.erase(name);
}

void PersistentWorker::workerFunction()
{
    while (!shouldStop)
    {
        std::map<std::string, std::function<void()>> tasksCopy;

        // Copiar tarefas atuais para evitar deadlock durante execução
        {
            std::lock_guard<std::mutex> lock(tasksMutex);
            tasksCopy = tasks;
        }

        // Executar cada tarefa
        for (const auto &[name, task] : tasksCopy)
        {
            if (shouldStop)
                break;

            try
            {
                threadSafeCout << "Executing task: " << name << std::endl;
                task();
            }
            catch (const std::exception &e)
            {
                threadSafeCout << "Error in task '" << name << "': " << e.what() << std::endl;
            }
        }

        // Pequeno break "para cafe :D" entre ciclos de execução se não houver tarefas
        if (tasksCopy.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}