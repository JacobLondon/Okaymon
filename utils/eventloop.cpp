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

Eventloop::Eventloop
(size_t period_millis):
period_millis(period_millis),
target_millis(0),
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
    events.remove_if([&](Event a){
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

void loop(std::list<Event>& events)
{
    for (auto& event : events) {
        event.cb(event, event.client);
    }
}

void Eventloop::LoopOnce()
{
    const size_t now = TimeNowMillis();
    if ((now - target_millis) >= period_millis) {
        target_millis = now;
        loop(events);
    }
}

void Eventloop::Loop()
{
    while (true) {
        LoopOnce();
        TimeSleepMillis(2);
    }
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
