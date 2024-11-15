
#pragma once
#include <memory>
#include <stdexcept>

template <typename TType>
class Singleton
{
public:
    static TType *instance()
    {
        if (!m_instance)
        {
            throw std::runtime_error("Instance not yet created");
        }
        return m_instance.get();
    }

    template <typename... TArgs>
    static void instantiate(TArgs &&...p_args)
    {
        if (m_instance)
        {
            throw std::runtime_error("Instance already created");
        }
        m_instance = std::make_unique<TType>(std::forward<TArgs>(p_args)...);
    }

private:
    Singleton() = default;
    static std::unique_ptr<TType> m_instance;
};


template <typename TType>
std::unique_ptr<TType> Singleton<TType>::m_instance = nullptr;