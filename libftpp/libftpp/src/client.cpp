#include "client.hpp"

void Client::connect(const std::string &address, const size_t &port)
{
    if (isConnected)
    {
        threadSafeCout << "Error: Already connected to server" << std::endl;
        return;
    }
    threadSafeCout << "Connected to " << address << ":" << port << std::endl;
    isConnected = true;
}

void Client::disconnect()
{
    if (!isConnected)
    {
        threadSafeCout << "Error: Not connected to server" << std::endl;
        return;
    }
    threadSafeCout << "Disconnected from server" << std::endl;
    isConnected = false;
}

void Client::defineAction(int messageType, const std::function<void(const Message &msg)> &action)
{
    if (actions.find(messageType) != actions.end())
    {
        threadSafeCout << "Error: Action already defined for this message type" << std::endl;
        return;
    }
    actions[messageType] = action;
}

void Client::send(const Message &message)
{
    if (!isConnected)
    {
        threadSafeCout << "Error: Not connected to server" << std::endl;
        return;
    }

    threadSafeCout << "Sending message of type " << message.type() << std::endl;

    // Simulamos recebimento de resposta do tipo 3 quando enviamos mensagem tipo 1
    if (message.type() == 1)
    {
        Message response(3);
        int value;
        Message tempMsg = message; // fazer cópia para não modificar original
        tempMsg >> value;
        response << (value * 2); // dobrar o valor
        receivedMessages.push(response);
    }
}

void Client::update()
{
    if (!isConnected)
        return;

    // processaos as mensagens recebidas
    while (!receivedMessages.empty())
    {
        const Message &msg = receivedMessages.front();
        auto it = actions.find(msg.type());
        if (it != actions.end())
        {
            it->second(msg);
        }
        receivedMessages.pop();
    }
}