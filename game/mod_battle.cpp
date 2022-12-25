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

static void draw_healthbox
(Okaymon& m, float offx, float offy)
{
    constexpr int fontsize = 24;
    constexpr int segments = 8;

    Rectangle hpbox = Rectangle{
        offx,
        offy,
        GetScreenWidth() * 0.4f,
        GetScreenHeight() * 0.2f
    };
    DrawRectangleRounded(hpbox, 0.5, segments, BLACK);

    Rectangle innerbox = hpbox;
    innerbox.x += 2;
    innerbox.y += 2;
    innerbox.width -= 4;
    innerbox.height -= 4;
    DrawRectangleRounded(innerbox, 0.5, segments, LIGHTGRAY);
    DrawText(
        m.name,
        innerbox.x + innerbox.width * 0.1f,
        innerbox.y + innerbox.height * 0.2f,
        fontsize,
        BLACK);

    Rectangle healthbg_rect = hpbox;
    healthbg_rect.x += healthbg_rect.width * 0.1f;
    healthbg_rect.y += healthbg_rect.height * 0.5f;
    healthbg_rect.width = healthbg_rect.width * 0.8f;
    healthbg_rect.height = healthbg_rect.height * 0.2f;
    DrawRectangleRec(healthbg_rect, BLACK);

    Rectangle healthfg_rect = healthbg_rect;
    const float ratio = (m.health / m.healthmax);
    healthfg_rect.x += 2;
    healthfg_rect.y += 2;
    healthfg_rect.width -= 4;
    healthfg_rect.height -= 4;
    healthfg_rect.width *= ratio;
    DrawRectangleRec(healthfg_rect,
        (ratio >= 0.5f)
        ? GREEN
        : ((ratio >= 0.25f)
            ? YELLOW
            : RED));

    char buf[32];
    snprintf(buf, sizeof(buf), "%.0f/%.0f", m.health, m.healthmax);
    DrawText(buf,
        healthbg_rect.x + healthbg_rect.width * 0.7,
        healthbg_rect.y + fontsize * 1.5,
        fontsize,
        BLACK);
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

    draw_healthbox(*opponent, GetScreenWidth() * 0.05f, GetScreenHeight() * 0.05f);
    draw_healthbox(*self, GetScreenWidth() * 0.55f, GetScreenHeight() * 0.45f);

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
