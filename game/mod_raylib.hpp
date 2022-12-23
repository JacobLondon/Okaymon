#pragma once

#include <utils/modules.hpp>
#include <raylib.h>

namespace Okay {

class Raylib : public Module {
    void init();
    void cleanup();
};

}
