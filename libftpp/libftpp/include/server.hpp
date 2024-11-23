#pragma once
#include <functional>
#include <map>
#include <vector>
#include <queue>
#include "message.hpp"
#include "thread_safe_iostream.hpp"

struct ReceivedMessage
{
    long long clientId;
    Message msg;

    ReceivedMessage(long long id, const Message &message)
        : clientId(id), msg(message) {}
};

class Server
{
public:
    void start(const size_t &p_port);

    void defineAction(int messageType,
                      const std::function<void(long long &clientID, const Message &msg)> &action);

    void sendTo(const Message &message, long long clientID);
    void sendToArray(const Message &message, std::vector<long long> clientIDs);
    void sendToAll(const Message &message);
    void update();

private:
    std::map<int, std::function<void(long long &, const Message &)>> actions;
    std::queue<ReceivedMessage> receivedMessages; // Simula mensagens recebidas socket :P
    std::vector<long long> connectedClients;      // Lista de clientes conectados
    bool isRunning = false;
    size_t port = 0;

    void simulateClientConnection(long long clientId);
};