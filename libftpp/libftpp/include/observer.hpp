
#pragma once
#include <unordered_map>
#include <functional>
#include <vector>

template <typename TEvent>
class Observer
{
public:
    void subscribe(const TEvent &event, const std::function<void()> &lambda)
    {
        
        subscribers[event].push_back(lambda);
    }


    void notify(const TEvent &event) const
    {
        auto it = subscribers.find(event);
        if (it != subscribers.end())
        {
            for (const auto &lambda : it->second)
            {
                lambda();
            }
        }
    }

private:
    std::unordered_map<TEvent, std::vector<std::function<void()>>> subscribers;
};