#include "memento.hpp"


Memento::Snapshot Memento::save() 
{
    Snapshot snapshot;
    _saveToSnapshot(snapshot);
    return snapshot;
}

void Memento::load( Memento::Snapshot &snapshot)
{
     _loadFromSnapshot(snapshot);
}

