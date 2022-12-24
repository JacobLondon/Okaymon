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

    ModulesSubscribe("ModBattle.Update", update, NULL, 0);
}

void ModBattle::cleanup()
{

}

static void end_encounter()
{
    ModulesResume("ModWorld.Update");
    ModulesPause("ModBattle.Update");
}

static void update
(Event& e, void *client)
{
    (void)e;
    (void)client;

    if (IsKeyPressed(KEY_R)) {
        end_encounter();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    auto myself = (const char *)ModulesSlotsGetRequired("ModBattle.Input.Self");
    auto myopponent = (const char *)ModulesSlotsGetRequired("ModBattle.Input.Other");

    auto self = (Okaymon *)ModulesSlotsGet(myself);
    auto opponent = (Okaymon *)ModulesSlotsGet(myopponent);

    self->Draw(0.1, 0.6);
    opponent->Draw(0.7, 0.1);

    EndDrawing();
}

}
