#include "eventloop.hpp"
#include "time.hpp"
#include <assert.h>

namespace Okay {

Event::Event
(const char *name, EventCb cb, void *client, size_t milliseconds):
again(true),
paused(false),
milliseconds(milliseconds),
name(name),
cb(cb),
client(client)
{
}

Eventloop::Eventloop():
done(false),
events{}
{
}

void Eventloop::Subscribe
(const char *name, EventCb cb, void *client, size_t milliseconds)
{
    events.emplace_back(name, cb, client, milliseconds);
}

void Eventloop::Unsubscribe
(const char *name)
{
    events.remove_if([&](Event& a){
        return strcmp(a.name, name) == 0;
    });
}

void Eventloop::Pause
(const char *name)
{
    Event *e = find(name);
    if (!e) return;
    e->paused = true;
}

void Eventloop::Resume
(const char *name)
{
    Event *e = find(name);
    if (!e) return;
    e->paused = false;
}

void Eventloop::LoopOnce()
{
    const size_t now = TimeNowMillis();
    for (auto& event : events) {
        if (event.paused) continue;
        if ((now - event.last_milliseconds) < event.milliseconds) continue;
        event.cb(event, event.client);
    }

    events.remove_if([](Event& a){
        return !a.again;
    });
}

void Eventloop::Loop()
{
    while (!done) {
        LoopOnce();
    }
}

void Eventloop::Stop()
{
    done = true;
}

void Eventloop::Stop
(const char *name)
{
    Event *e = find(name);
    if (!e) return;
    e->again = false;
}

Event *Eventloop::find
(const char *name)
{
    assert(name != NULL);

    for (auto& event : events) {
        if (strcmp(event.name, name) == 0) {
            return &event;
        }
    }
    return NULL;
}

}
