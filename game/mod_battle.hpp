#pragma once

#include <utils/modules.hpp>

namespace Okay {

class Battle : public Module {
    void init();
    void cleanup();
};

static Module *GetBattle()
{
    return new Battle();
}

}
