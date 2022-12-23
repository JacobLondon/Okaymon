#include "modules.hpp"
#include "slots.hpp"
#include <list>
#include <assert.h>

namespace Okay {

static Slots _slots;
static Eventloop *_eventloop;
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
    _modules.clear();
    _loaded.clear();
    _slots.Clear();
}

void ModulesLoop()
{
    _eventloop->Loop();
}

Eventloop *ModulesGetEventloop()
{
    assert(_eventloop != NULL);
    return _eventloop;
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
    assert(_eventloop != NULL);
    _eventloop->Stop();
}

void ModulesSlotsInsert
(const char *name, void *data)
{
    assert(name != NULL);
    _slots.Insert(name, data);
}

void *ModulesSlotsGet
(const char *name)
{
    assert(name != NULL);
    return _slots.Get(name);
}

}
