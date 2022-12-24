#include "mod_battle.hpp"
#include "mod_okaymon.hpp"
#include "mod_raylib.hpp"
#include "mod_moves.hpp"
#include "mod_world.hpp"

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
    };

    ModulesInit(defs);
    ModulesLoop();
    ModulesCleanup();

    return 0;
}

}
