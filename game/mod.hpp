#pragma once

#include <utils/modules.hpp>

namespace Okay {

class ModBattle : public Module {
    void init();
    void cleanup();
};

class ModMoves : public Module {
    void init();
    void cleanup();
};

class ModOkaymon : public Module {
    void init();
    void cleanup();
};

class ModRaylib : public Module {
    void init();
    void cleanup();
};

class ModWorld : public Module {
    void init();
    void cleanup();
};

class ModMessages : public Module {
    void init();
    void cleanup();
};

}