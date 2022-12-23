#pragma once

#include <utils/modules.hpp>

namespace Okay {

class Raylib : public Module {
    void init();
    void cleanup();
};

static Module *GetRaylib()
{
    return new Raylib();
}

}
