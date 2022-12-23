#include <utils/modules.hpp>
#include "mod_raylib.hpp"

namespace Okay {

void Raylib::init() {
    Eventloop *e = ModulesGetEventloop();
    (void)e;
}

void Raylib::cleanup() {

}

}
