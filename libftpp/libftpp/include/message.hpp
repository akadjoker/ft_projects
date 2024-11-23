#pragma once

#include <iostream>
#include <vector>
#include <sstream>

class Message
{
private:
    int messageType;
    std::vector<char> data;
    mutable size_t readPosition = 0; // OBS
                                     /*
                                      * A palavra-chave mutable indica que o membro pode ser modificado em tempo de execução.
                                      * No caso do readPosition, ele poderia ser modificado em tempo de execução, mas aqui é apenas para leitura.
                                      */
public:
    explicit Message(int type); // OBS
    /*
    O explicit é usado para evitar conversões implícitas não desejadas em construtores que aceitam um único argumento.

    Message msg = 42;  // Conversão implícita de int para Message

    // Isto provoca um erro de compilação:
    // Message msg = 42;

    // Agora isto NÃO compila:
    Message msg = 42;  // Erro! Conversão implícita não permitida :P

    // Tem que ser explícito:
    Message msg(42);     // OK
    Message msg = Message(42);  // OK também


    */

    Message(const Message &other) : messageType(other.messageType) {}

    Message() : messageType(0) {}

    int type() const;

    void setType(int type) { messageType = type; }

    template <typename T>
    Message &operator<<(const T &value)
    {
        std::string str = std::to_string(value);
        data.insert(data.end(), str.begin(), str.end());
        data.push_back('\n');
        return *this;
    }

    Message &operator<<(const char &value)
    {
        data.push_back(value);
        data.push_back('\n');
        return *this;
    }

    template <typename T>
    const Message &operator>>(T &value) const
    {
        if (readPosition >= data.size())
            return *this;

        std::string str;
        while (readPosition < data.size() && data[readPosition] != '\n')
        {
            str += data[readPosition++];
        }
        readPosition++; // skip \n

        std::stringstream ss(str);
        ss >> value;

        return *this;
    }
};
