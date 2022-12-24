#include "modules.hpp"
#include "slots.hpp"
#include "misc.hpp"
#include <list>
#include <stdarg.h>
#include <assert.h>
#include <raylib.h>

namespace Okay {

static Slots _slots;
static Eventloop *_eventloop;
static Nexus _nexus;
static std::list<Module *> _modules;
static std::list<const char *> _loaded;

void ModulesInit
(std::list<ModuleDef>& defs)
{
    _eventloop = new Eventloop();

    for (auto& def : defs) {
        Module *m = def.getter();
        _modules.push_back(m);
        m->init();
        _loaded.push_back(def.name);
    }
}

void ModulesCleanup()
{
    for (auto& module : _modules) {
        module->cleanup();
    }

    delete _eventloop;
    _nexus.Clear();
    _modules.clear();
    _loaded.clear();
    _slots.Clear();
}

void ModulesLoop()
{
    _eventloop->Loop();
}

bool ModulesLoaded(const char *name)
{
    if (!name) return false;
    for (auto& loaded_name : _loaded) {
        if (strcmp(name, loaded_name) == 0) {
            return true;
        }
    }
    return false;
}

void ModulesRequestStop()
{
    Assert(_eventloop != NULL);
    _eventloop->Stop();
}

void ModulesSlotsInsert
(const char *name, void *data, void (* dealloc)(void *))
{
    Assert(name != NULL);
    _slots.Insert(name, data, dealloc);
}

void *ModulesSlotsGet
(const char *name)
{
    Assert(name != NULL);
    return _slots.Get(name);
}

void *ModulesSlotsGetRequired
(const char *name)
{
    void *p = ModulesSlotsGet(name);
    TraceAssert(p != NULL, "Module: Cannot get slot: %s", name);
    return p;
}

void ModulesPause(const char *name)
{
    Assert(_eventloop != NULL);
    _eventloop->Pause(name);
}

void ModulesResume(const char *name)
{
    Assert(_eventloop != NULL);
    _eventloop->Resume(name);
}

void ModulesTimeoutSubscribe
(const char *name, Okay::EventCb cb, void *client, size_t milliseconds)
{
    Assert(name != NULL);
    Assert(_eventloop != NULL);
    _eventloop->Subscribe(name, cb, client, milliseconds);
}

void ModulesTimeoutUnsubscribe
(const char *name)
{
    Assert(name != NULL);
    Assert(_eventloop != NULL);
    _eventloop->Unsubscribe(name);
}

void ModulesNexusSubscribe
(const char *name, NexusCb cb)
{
    Assert(name != NULL);
    Assert(cb != NULL);
    _nexus.Subscribe(name, cb);
}

void ModulesNexusUnsubscribe
(const char *name)
{
    Assert(name != NULL);
    _nexus.Unsubscribe(name);
}

void ModulesNexusPublish
(const char *name, void *data)
{
    Assert(name != NULL);
    _nexus.Publish(name, data);
}

void ModulesNexusPublish
(const char *name, const char *fmt, ...)
{
    Assert(name != NULL);
    Assert(fmt != NULL);
    static char buf[1024];

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    _nexus.Publish(name, (void *)buf);
}

}
