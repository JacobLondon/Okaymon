#include "nexus.hpp"
#include "misc.hpp"

namespace Okay {

Nexus::Nexus():
observers{}
{
}

void Nexus::Subscribe
(const char *name, NexusCb cb)
{
    Assert(name != NULL);
    Assert(cb != NULL);

    auto got = observers.find(name);
    if (got == observers.end()) {
        observers.insert_or_assign(name, std::list{cb});
        return;
    }

    got->second.emplace_back(cb);
}

void Nexus::Unsubscribe
(const char *name)
{
    Assert(name != NULL);
    observers.erase(name);
}

void Nexus::Publish
(const char *name, void *data)
{
    Assert(name != NULL);

    auto got = observers.find(name);
    if (got == observers.end()) {
        return;
    }

    for (NexusCb& cb : got->second) {
        cb(data);
    }
}

void Nexus::Clear()
{
    observers.clear();
}

}
