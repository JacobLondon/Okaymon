#include "mod.hpp"

namespace Okay {

int Entry
(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    std::list<ModuleDef> defs = {
        ModuleDef_StaticInitializer(ModRaylib),
        ModuleDef_StaticInitializer(ModMoves),
        ModuleDef_StaticInitializer(ModOkaymon),

        ModuleDef_StaticInitializer(ModBattle),
        ModuleDef_StaticInitializer(ModWorld),
        ModuleDef_StaticInitializer(ModMessages),
    };

    ModulesInit(defs);
    ModulesLoop();
    ModulesCleanup();

    return 0;
}

}
