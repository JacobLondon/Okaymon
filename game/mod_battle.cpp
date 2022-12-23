#include <utils/modules.hpp>
#include "mod_battle.hpp"
#include <raylib.h>

namespace Okay {

static void update(Event& e, void *client);

static Texture2D *mudkip;

void Battle::init()
{
    assert(ModulesLoaded("Raylib"));

    Eventloop *e = ModulesGetEventloop();
    e->Subscribe("Battle", update, NULL, 16);

    mudkip = (Texture2D *)ModulesSlotsGet("assets/mudkip.png");
}

void Battle::cleanup()
{

}

static void update
(Event& e, void *client)
{
    (void)e;
    (void)client;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(*mudkip, 0, 0, WHITE);
    EndDrawing();
}

}
