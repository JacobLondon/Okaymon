#pragma once
#include <list>
#include "eventloop.hpp"

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

void ModulesInit(std::list<ModuleDef>& defs);
void ModulesLoop();
void ModulesCleanup();

void ModulesRequestStop();

Eventloop *ModulesGetEventloop();
bool ModulesLoaded(const char *name);

}
