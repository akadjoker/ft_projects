
#pragma once
#include <vector>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include "data_buffer.hpp"


class DataBuffer
{
public:

    template <typename T>
    DataBuffer &operator<<(const T &value)
    {
        static_assert(std::is_trivially_copyable<T>::value, "value T must be trivially copyable");
        size_t currentSize = buffer.size();
        buffer.resize(currentSize + sizeof(T));
        std::memcpy(&buffer[currentSize], &value, sizeof(T));
        return *this;
    }


    template <typename T>
    DataBuffer &operator>>(T &value)
    {
         static_assert(std::is_trivially_copyable<T>::value, "value T must be trivially copyable");

        if (readPos + sizeof(T) > buffer.size())
        {
            throw std::out_of_range("Not enough data in the buffer to read");
        }

        std::memcpy(&value, &buffer[readPos], sizeof(T));
        readPos += sizeof(T);
        return *this;
    }

    DataBuffer &operator<<(const std::string &str);
    DataBuffer &operator>>(std::string &str);

private:
    friend class Memento;

    std::vector<char> buffer;
    size_t readPos = 0;
};
