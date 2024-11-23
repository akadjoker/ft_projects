#pragma once

#include "data_buffer.hpp"
class DataBuffer;

class Memento
{
public:
    class Snapshot
    {
    public:
        DataBuffer buffer;

        template <typename T>
        Snapshot &operator<<(const T &value)
        {
            buffer << value;
            return *this;
        }

        template <typename T>
        Snapshot &operator>>(T &value)
        {
            buffer >> value;
            return *this;
        }
    };

    Memento::Snapshot save();
    void load( Memento::Snapshot &snapshot);

protected:
    
    virtual void _saveToSnapshot(Memento::Snapshot &snapshot) = 0;
    virtual void _loadFromSnapshot( Memento::Snapshot &snapshot) = 0;
};
