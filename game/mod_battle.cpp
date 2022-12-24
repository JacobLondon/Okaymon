#include <utils/modules.hpp>
#include "mod.hpp"
#include "okaymon.hpp"
#include <raylib.h>
#include <raygui.h>

namespace Okay {

static void update(Event& e, void *client);

void ModBattle::init()
{
    Assert(ModulesLoaded("ModRaylib"));
    Assert(ModulesLoaded("ModOkaymon"));

    ModulesTimeoutSubscribe("ModBattle.Update", update, NULL, 0);
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

    // draw okaymon
    self->Draw(0.1, 0.4);
    opponent->Draw(0.7, 0.1);

    // draw move options
    Rectangle rect = Rectangle{0, GetScreenHeight() * 0.7f, (float)GetScreenWidth(), GetScreenHeight() * 0.3f};
    DrawRectangleRec(rect, GRAY);
    Rectangle b1 = rect;
    b1.width /= 2;
    b1.height /= 2;

    Rectangle b2 = b1;
    b2.x = GetScreenWidth() / 2;

    Rectangle b3 = b1;
    b3.y += b3.height;

    Rectangle b4 = b2;
    b4.y += b4.height;

    if (GuiButton(b1, self->moves[0]->name)) {
        self->moves[0]->Activate(*self, *opponent);
    }
    else if (GuiButton(b2, self->moves[1]->name)) {
        self->moves[1]->Activate(*self, *opponent);
    }
    else if (GuiButton(b3, self->moves[2]->name)) {
        self->moves[2]->Activate(*self, *opponent);
    }
    else if (GuiButton(b4, self->moves[3]->name)) {
        self->moves[3]->Activate(*self, *opponent);
    }

    EndDrawing();
}

}
