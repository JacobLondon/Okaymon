#include "slots.hpp"
#include "misc.hpp"

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
    Assert(name != NULL);
    Slot slot{name, data, dealloc};
    auto got = slots.find(name);
    if (got == slots.end()) {
        slots.emplace(name, slot);
        return;
    }

    if (got->second.dealloc) {
        got->second.dealloc(got->second.data);
    }
    slots.insert_or_assign(name, slot);
}

void *Slots::Get
(const char *name)
{
    Assert(name != NULL);
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
