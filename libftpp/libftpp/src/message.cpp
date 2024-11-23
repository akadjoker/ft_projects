
#include "message.hpp"

Message::Message(int type) : messageType(type) {}

int Message::type() const
{
    return messageType;
}
// template <typename T>
// std::ostream &operator<<(std::ostream &os, const Message &msg)
// {
//     os << "Message Type: " << msg.messageType;
//     return os;
// }

// template <typename T>
// std::istream &operator>>(std::istream &is, Message &msg)
// {
//     is >> msg.messageType;
//     return is;
// }

// template std::ostream &operator<< <int>(std::ostream &os, const Message &msg);
// template std::istream &operator>> <int>(std::istream &is, Message &msg);
