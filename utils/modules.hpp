#pragma once
#include <list>
#include "eventloop.hpp"
#include "misc.hpp"

namespace Okay {

struct Module {
    virtual void init() = 0;
    virtual void cleanup() = 0;
};

typedef Module *(* ModuleGetter)();

struct ModuleDef {
    const char *name;
    ModuleGetter getter;
};

#define ModuleDef_StaticInitializer(Name) \
    ModuleDef{ \
        #Name, \
        []() -> Module *{ return new Name(); }, \
    }

void ModulesInit(std::list<ModuleDef>& defs);
void ModulesLoop();
void ModulesCleanup();

void ModulesRequestStop();

Eventloop *ModulesGetEventloop();
bool ModulesLoaded(const char *name);
void ModulesSlotsInsert(const char *name, void *data, void (* dealloc)(void *));
void *ModulesSlotsGet(const char *name);
void *ModulesSlotsGetRequired(const char *name);

}
