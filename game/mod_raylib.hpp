#pragma once

#include <utils/modules.hpp>
#include <raylib.h>

namespace Okay {

class ModRaylib : public Module {
    void init();
    void cleanup();
};

}
