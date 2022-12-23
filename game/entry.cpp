#include <utils/modules.hpp>
#include "battle.hpp"
#include <raylib.h>

namespace Okay {

int Entry(int argc, char **argv) {
    (void)argc;
    (void)argv;

    std::list<ModuleDef> defs = {
        {"Battle", GetBattle},
    };

    ModulesInit(defs);
    ModulesLoop();
    ModulesCleanup();

    return 0;
}

}
