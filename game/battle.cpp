#include <utils/modules.hpp>
#include <utils/eventloop.hpp>
#include "battle.hpp"

namespace Okay {

static void update(Event& e, void *client);

void Battle::init() {
    assert(ModulesLoaded("Raylib"));
}

void Battle::cleanup() {

}

static void update(Event& e, void *client)
{
    (void)e;
    (void)client;
}

}
