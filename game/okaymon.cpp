#include "okaymon.hpp"
#include <utils/modules.hpp>

namespace Okay {

Okaymon::Okaymon():
name(""),
attack(0),
attackmax(0),
defense(0),
defensemax(0),
health(0),
healthmax(0),
texture(nullptr),
autoscale(0),
moves{}
{}

Okaymon::Okaymon(Okaymon& m):
name(m.name),
attack(m.attack),
attackmax(m.attackmax),
defense(m.defense),
defensemax(m.defensemax),
health(m.health),
healthmax(m.healthmax),
texture(m.texture),
autoscale(m.autoscale),
moves(m.moves)
{
}

Okaymon::Okaymon
(OkaymonDef& def):
name(def.name),
attack(def.attack),
attackmax(def.attack),
defense(def.defense),
defensemax(def.defense),
health(def.health),
healthmax(def.health),
texture(nullptr),
autoscale(1.0f),
moves{}
{
    texture = (Texture2D *)ModulesSlotsGetRequired(def.filename);

    // scale all okaymon to be the same size based on the window size
    autoscale = TextureCalculateScale(texture, OKAYMON_SCALE_SIZE);

    for (size_t i = 0; i < def.moves.size(); i++) {
        moves[i] = (Move *)ModulesSlotsGetRequired(def.moves[i]);
    }
}

void Okaymon::Draw
(float x, float y)
{
    x = GetScreenWidth() * x;
    y = GetScreenHeight() * y;

    DrawTextureEx(*texture, Vector2{x, y}, 0, autoscale, WHITE);
}

}
