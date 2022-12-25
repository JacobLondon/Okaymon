#include <raylib.h>
#include "mod.hpp"
#include <utils/modules.hpp>

namespace Okay {

static void update(Okay::Event &e, void *client);

void ModWorld::init()
{
    Assert(ModulesLoaded("ModRaylib"));
    Assert(ModulesLoaded("ModBattle"));

    ModulesPause("ModBattle.Update");
    ModulesTimeoutSubscribe("ModWorld.Update", update, NULL, 0);
}

void ModWorld::cleanup()
{

}

static void begin_encounter()
{
    ModulesResume("ModBattle.Update");
    ModulesPause("ModWorld.Update");

    ModulesSlotsInsert("ModBattle.Input.Self", (void *)"Okaymon.Mudkip", NULL);
    ModulesSlotsInsert("ModBattle.Input.Other", (void *)"Okaymon.Vaporeon", NULL);
}

static void update
(Event &e, void *client)
{
    (void)e;
    (void)client;

    if (IsKeyPressed(KEY_SPACE)) {
        begin_encounter();
    }

    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
}

}
