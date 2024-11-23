#include "server.hpp"
#include <algorithm>

void Server::start(const size_t &p_port)
{
    port = p_port;
    isRunning = true;
    threadSafeCout << "Server started on port " << port << std::endl;

    // simulamos conexão de clientes , śo dois :O
    simulateClientConnection(1);
    simulateClientConnection(2);
}

void Server::defineAction(int messageType,
                          const std::function<void(long long &, const Message &msg)> &action)
{
    actions[messageType] = action;
}

void Server::sendTo(const Message &message, long long clientID)
{
    (void)clientID;
    (void)message;
    if (!isRunning)
    {
        threadSafeCout << "Error: Server not running" << std::endl;
        return;
    }

    auto it = std::find(connectedClients.begin(), connectedClients.end(), clientID);
    if (it != connectedClients.end())
    {
        threadSafeCout << "Sending message to client " << clientID << std::endl;
    }
    else
    {
        threadSafeCout << "Error: Client " << clientID << " not connected" << std::endl;
    }
}

void Server::sendToArray(const Message &message, std::vector<long long> clientIDs)
{
    for (const auto &clientID : clientIDs)
    {
        sendTo(message, clientID);
    }
}

void Server::sendToAll(const Message &message)
{
    for (const auto &clientID : connectedClients)
    {
        sendTo(message, clientID);
    }
}

void Server::update()
{
    if (!isRunning)
        return;

    // Simular recebimento de mensagens
    if (connectedClients.size() > 0)
    {
        // Simular mensagem tipo 1 do cliente 1
        static bool sentMsg1 = false;
        if (!sentMsg1)
        {
            Message msg1(1);
            msg1 << 42;
            receivedMessages.push(ReceivedMessage(1, msg1));
            sentMsg1 = true;
        }

        // Simular mensagem tipo 2 do cliente 2
        static bool sentMsg2 = false;
        if (!sentMsg2)
        {
            Message msg2(2);
            std::string str = "Hello";
            msg2 << str.size();
            for (char c : str)
            {
                msg2 << c;
            }
            receivedMessages.push(ReceivedMessage(2, msg2));
            sentMsg2 = true;
        }
    }

    // Processar mensagens recebidas
    while (!receivedMessages.empty())
    {
        auto &received = receivedMessages.front();
        auto it = actions.find(received.msg.type());
        if (it != actions.end())
        {
            it->second(received.clientId, received.msg);
        }
        receivedMessages.pop();
    }
}

void Server::simulateClientConnection(long long clientId)
{
    connectedClients.push_back(clientId);
    threadSafeCout << "Client " << clientId << " connected" << std::endl;
}