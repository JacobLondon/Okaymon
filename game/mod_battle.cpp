#include <utils/modules.hpp>
#include "mod_battle.hpp"
#include "okaymon.hpp"
#include <raylib.h>

namespace Okay {

static void update(Event& e, void *client);

void ModBattle::init()
{
    Assert(ModulesLoaded("ModRaylib"));
    Assert(ModulesLoaded("ModOkaymon"));

    Eventloop *e = ModulesGetEventloop();
    e->Subscribe("Battle", update, NULL, 0);
}

void ModBattle::cleanup()
{

}

static void update
(Event& e, void *client)
{
    (void)e;
    (void)client;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    auto *mudkip = (Okaymon *)ModulesSlotsGet("Okaymon.Mudkip");
    auto *vaporeon = (Okaymon *)ModulesSlotsGet("Okaymon.Vaporeon");

    mudkip->Draw(0.1, 0.6);
    vaporeon->Draw(0.7, 0.1);

    EndDrawing();
}

}
