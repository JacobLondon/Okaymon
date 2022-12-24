#pragma once
#include <array>
#include <raylib.h>
#include "moves.hpp"

namespace Okay {

#define OKAYMON_SCALE_SIZE 0.25f

struct OkaymonDef {
    const char *name;
    const char *filename;
    std::array<const char *, 4> moves;
    float attack;
    float defense;
    float health;
};

struct Okaymon {
    const char *name;
    float attack;
    float defense;
    float health;
    Texture2D *texture;
    float autoscale;
    std::array<Move *, 4> moves;

    Okaymon();
    Okaymon(OkaymonDef& def);
    void Draw(float x, float y);
};

}
