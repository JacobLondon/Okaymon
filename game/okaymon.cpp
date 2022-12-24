#include "okaymon.hpp"
#include <utils/modules.hpp>

namespace Okay {

Okaymon::Okaymon():
name(""),
attack(0),
defense(0),
health(0),
texture(nullptr),
autoscale(0),
moves{}
{}

Okaymon::Okaymon
(OkaymonDef& def):
name(def.name),
attack(def.attack),
defense(def.defense),
health(def.health),
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
