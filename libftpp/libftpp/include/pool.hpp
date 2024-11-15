#pragma once
#include <vector>
#include <new>
#include <cstddef>

#if defined(VERBOSE)
#include "Utils.hpp"
#endif

template <typename TType>
class Pool
{
public:

    class Object
    {
    public:
    
        Object(TType *ptr, Pool<TType> *pool) : m_ptr(ptr), m_pool(pool) {}


        //  Construtor de cópia (proibido)
        Object(const Object& other) = delete;

        //  Operador de atribuição de cópia (proibido)
        Object& operator=(const Object& other) = delete;

        // Construtor de movimentação (necessário pela Regra dos 5)
        Object(Object &&other) noexcept : m_ptr(other.m_ptr), m_pool(other.m_pool)
        {
            other.m_ptr = nullptr;
            other.m_pool = nullptr;
        }

        // Operador de atribuição de movimentação (necessário pela Regra dos 5)
        Object &operator=(Object &&other) noexcept
        {
            if (this != &other)
            {
                if (m_ptr != nullptr)
                {
                    m_pool->release(m_ptr);
                }
                m_ptr = other.m_ptr;
                m_pool = other.m_pool;
                other.m_ptr = nullptr;
                other.m_pool = nullptr;
            }
            return *this;
        }

        ~Object()
        {
            if (m_ptr != nullptr)
            { 
                m_pool->release(m_ptr); 
            }
        }

   
        TType *operator->()        {            return m_ptr;        }


    private:
        TType *m_ptr;       
        Pool<TType> *m_pool; 
    };


    Pool() = default;
    ~Pool()
    {
        clear();
    }


    void resize(const size_t &numberOfObjectsStored)
    {
        for (size_t i = 0; i < numberOfObjectsStored; ++i)
        {
            // Aloca a memória e constrói o objeto chamando o construtor padrão
            TType *obj = new TType(); 

 
            #if defined(VERBOSE)

                INFO("Create object %p", obj);

            #endif

            m_pool.push_back(obj);
        }
    }


    template <typename... TArgs>
    Object acquire(TArgs &&...args)
    {
        if (!m_pool.empty())
        {
            TType *obj = m_pool.back();
            m_pool.pop_back(); // Remove o objeto do pool
            if constexpr (sizeof...(TArgs) > 0) 
            {
                obj->~TType(); //chama o destrutor do objeto
                new (obj) TType(std::forward<TArgs>(args)...);
            }
             
        #if defined(VERBOSE)

            INFO("Retrieved object %p", obj);

        #endif
            return Object(obj, this); // Retorna o objeto
        }
        else
        {
            return Object(new TType(std::forward<TArgs>(args)...), this);
        }
    }

    void release(TType *obj)
    {
        #if defined(VERBOSE)
            INFO("Releasing object %p", obj);
        #endif
        m_pool.push_back(obj); 
    }

private:
    std::vector<TType *> m_pool; 


    void clear()
    {
        for (TType *obj : m_pool)
        {
            #if defined(VERBOSE)
                INFO("Delete object %p", obj);
            #endif
            delete obj; // Liberta a memória alocada para cada objeto
        }
        m_pool.clear(); 
    }
};
