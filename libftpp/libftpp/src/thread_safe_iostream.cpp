#include "thread_safe_iostream.hpp"

// Definição  estáticas
thread_local std::string ThreadSafeIOStream::threadPrefix;
thread_local std::stringstream ThreadSafeIOStream::buffer;
std::mutex ThreadSafeIOStream::s_mutex;

// Definição d global
thread_local ThreadSafeIOStream threadSafeCout;

void ThreadSafeIOStream::setPrefix(const std::string &prefix)
{
    threadPrefix = prefix;
}
