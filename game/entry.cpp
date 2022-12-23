#include "mod_battle.hpp"
#include "mod_raylib.hpp"

namespace Okay {

int Entry
(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    std::list<ModuleDef> defs = {
        ModuleDef_StaticInitializer(Raylib),
        ModuleDef_StaticInitializer(Battle),
    };

    ModulesInit(defs);
    ModulesLoop();
    ModulesCleanup();

    return 0;
}

}
