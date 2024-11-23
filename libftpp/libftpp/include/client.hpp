#pragma once

#include <string>
#include <functional>
#include <map>
#include <queue>
#include "message.hpp"
#include "thread_safe_iostream.hpp"

class Client
{
public:
    void connect(const std::string &address, const size_t &port);
    void disconnect();
    void defineAction(int messageType, const std::function<void(const Message &msg)> &action);
    void send(const Message &message);
    void update();

private:
    std::map<int, std::function<void(const Message &)>> actions;
    std::queue<Message> receivedMessages; // Simula mensagens recebidas :( queria sockets :P
    bool isConnected = false;
};
