#include "slots.hpp"

namespace Okay {

Slots::Slots():
slots{}
{
}

void Slots::Insert
(const char *name, void *data)
{
    Insert(name, data, NULL);
}

void Slots::Insert
(const char *name, void *data, void (* dealloc)(void *))
{
    assert(name != NULL);
    Slot slot{name, data, dealloc};
    slots.insert_or_assign(name, slot);
}

void *Slots::Get
(const char *name)
{
    assert(name != NULL);
    auto got = slots.find(name);
    if (got == slots.end()) {
        return NULL;
    }
    return got->second.data;
}

void Slots::Clear()
{
    for (auto& pair : slots) {
        if (pair.second.dealloc) {
            pair.second.dealloc(pair.second.data);
        }
    }

    slots.clear();
}

}
