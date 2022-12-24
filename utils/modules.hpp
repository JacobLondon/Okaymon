#pragma once
#include <list>
#include "eventloop.hpp"
#include "nexus.hpp"
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

bool ModulesLoaded(const char *name);
void ModulesSlotsInsert(const char *name, void *data, void (* dealloc)(void *));
void *ModulesSlotsGet(const char *name);
void *ModulesSlotsGetRequired(const char *name);

void ModulesPause(const char *name);
void ModulesResume(const char *name);
bool ModulesIsPaused(const char *name);

void ModulesTimeoutSubscribe(const char *name, EventCb cb, void *client, size_t milliseconds);
void ModulesTimeoutUnsubscribe(const char *name);

void ModulesNexusSubscribe(const char *name, NexusCb cb);
void ModulesNexusUnsubscribe(const char *name);
void ModulesNexusPublish(const char *name, void *data);
void ModulesNexusPublish(const char *name, const char *fmt, ...);

}
