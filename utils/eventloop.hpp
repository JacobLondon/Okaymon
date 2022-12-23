#pragma once
#include <list>
#include <string>

namespace Okay {

struct Event;

typedef void (*EventCb)(Event& e, void *client);

struct Event {
    Event(const char *name, EventCb cb, void *client, size_t milliseconds);
    bool again;
    bool paused;
    size_t milliseconds;
    size_t last_milliseconds;
    const char *name;

    EventCb cb;
    void *client;
};

class Eventloop {
public:
    Eventloop();
    void Subscribe(const char *name, EventCb cb, void *client, size_t milliseconds);
    void Unsubscribe(const char *name);
    void Pause(const char *name);
    void Resume(const char *name);
    void Loop();
    void LoopOnce();
    void Stop();
private:
    bool done;
    std::list<Event> events;

    Event *find(const char *name);
};
}
