#pragma once

#include <unordered_map>
#include <string>
#include <list>

namespace Okay {

typedef void (* NexusCb)(void *);

class Nexus {
public:
    Nexus();
    void Subscribe(const char *name, NexusCb cb);
    void Unsubscribe(const char *name);
    void Publish(const char *name, void *data);
    void Clear();

private:
    std::unordered_map<std::string, std::list<NexusCb>> observers;
};

}
