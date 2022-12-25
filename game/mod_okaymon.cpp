#include <utils/modules.hpp>
#include "mod.hpp"
#include "okaymon.hpp"

namespace Okay {

static OkaymonDef defs[] = {
    {
        "Okaymon.Mudkip", "assets/mudkip.png",
        {
            "Move.Muddy Water",
            "Move.Thunder Bolt",
            "Move.Psychic",
            "Move.Fire Blast",
        },
        20, 30, 50
    },
    {
        "Okaymon.Vaporeon", "assets/vaporeon.png",
        {
            "Move.Hydro Pump",
            "Move.Mega Punch",
            "Move.Ice Fang",
            "Move.Gunk Shot",
        },
        40, 20, 100
    },
};

void ModOkaymon::init()
{
    Assert(ModulesLoaded("ModRaylib"));
    Assert(ModulesLoaded("ModMoves"));

    for (size_t i = 0; i < ARRAY_SIZE(defs); i++) {
        Okaymon *m = new Okaymon(defs[i]);
        ModulesSlotsInsert(defs[i].name, m, [](void *_a){
            auto a = (Okaymon *)_a;
            delete a;
        });
    }
}

void ModOkaymon::cleanup()
{

}

}
