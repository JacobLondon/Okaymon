#include "mod_battle.hpp"
#include "mod_raylib.hpp"

namespace Okay {

int Entry(int argc, char **argv) {
    (void)argc;
    (void)argv;

    std::list<ModuleDef> defs = {
        {"Raylib", GetRaylib},
        {"Battle", GetBattle},
    };

    ModulesInit(defs);
    ModulesLoop();
    ModulesCleanup();

    return 0;
}

}
