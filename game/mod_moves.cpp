#include "mod.hpp"
#include "moves.hpp"

namespace Okay {

static Move moves[] = {
    {"Move.Hydro Pump",   110, .8},
    {"Move.Muddy Water",  90, .85},
    {"Move.Fire Blast",   110, .85},
    {"Move.Thunder Bolt", 90, 1.0},
    {"Move.Psychic",      90, 1.0},
    {"Move.Mega Punch",   80, .85},
    {"Move.Ice Fang",     65, .95},
    {"Move.Gunk Shot",    120, .8},
    {"Move.None",         0,   0},
};

void ModMoves::init()
{
    for (size_t i = 0; i < ARRAY_SIZE(moves); i++) {
        ModulesSlotsInsert(moves[i].name, &moves[i], NULL);
    }
}

void ModMoves::cleanup()
{

}

}
