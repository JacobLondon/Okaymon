#include "misc.hpp"
#include <algorithm> // min/max

float TextureCalculateScale
(Texture2D *texture, float scale)
{
    Assert(texture != NULL);

    // scale all okaymon to be the same size based on the window size
    const float unit_smallest = (float)std::max(texture->width, texture->height);
    const float screen_smallest = (float)std::min(GetScreenWidth(), GetScreenHeight());
    const float target = scale * screen_smallest;

    const float smallest = std::min(unit_smallest, target);
    const float largest = std::max(unit_smallest, target);
    const float autoscale = smallest / largest;
    return autoscale;
}
