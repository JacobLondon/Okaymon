#pragma once

#include <string>
#include <unordered_map>

namespace Okay {

struct Slot {
    const char *name;
    void *data;
    void (* dealloc)(void *);
};

class Slots {
public:
    Slots();
    void Insert(const char *name, void *data);
    void Insert(const char *name, void *data, void (* dealloc)(void *));
    void *Get(const char *name);
    void Clear();
private:
    std::unordered_map<std::string, Slot> slots;
};

}
