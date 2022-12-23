#include <utils/modules.hpp>
#include "mod_battle.hpp"

namespace Okay {

static void update(Event& e, void *client);

void Battle::init()
{
    assert(ModulesLoaded("Raylib"));

    Eventloop *e = ModulesGetEventloop();
    e->Subscribe("Battle", update, NULL, 16);
}

void Battle::cleanup()
{

}

static void update
(Event& e, void *client)
{
    (void)e;
    (void)client;
}

}
