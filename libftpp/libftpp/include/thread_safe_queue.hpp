#pragma once
#include <mutex>
#include <deque>
#include <stdexcept>

template <typename TType>
class ThreadSafeQueue
{
public:
  
    ThreadSafeQueue() = default;

    void push_back(const TType &newElement)
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push_back(newElement);
    }


    void push_front(const TType &newElement)
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push_front(newElement);
    }


    TType pop_back()
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        TType element = queue.back();
        queue.pop_back();
        return element;
    }

 
    TType pop_front()
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        TType element = queue.front();
        queue.pop_front();
        return element;
    }

private:
    std::deque<TType> queue; //  deque para suportar operações em ambas as extremidades <- ->
    std::mutex mutex;        // Mutex para garantir thread-safety
};

