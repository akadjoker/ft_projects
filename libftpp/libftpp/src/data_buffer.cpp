#include "data_buffer.hpp"
#include "memento.hpp"

DataBuffer &DataBuffer::operator<<(const std::string &str)
{
    // Serializa o comprimento da string primeiro
    size_t length = str.size();
    *this << length; // Usa o operador << para serializar o comprimento

    // Serializa os caracteres da string
    buffer.insert(buffer.end(), str.begin(), str.end());
    return *this;
}

DataBuffer &DataBuffer::operator>>(std::string &str)
{
    // Desserializa o comprimento da string
    size_t length;
    *this >> length; // Usa o operador >> para desserializar o comprimento

    if (readPos + length > buffer.size())
    {
        throw std::out_of_range("Not enough data in the buffer to read string");
    }

    // le os caracteres da string
    str.assign(&buffer[readPos], length);
    readPos += length;
    return *this;
}
