#include <utils/modules.hpp>
#include "mod_raylib.hpp"
#include <raylib.h>
#include <signal.h>

namespace Okay {

static void interrupt(int sig);
static void update(Event& e, void *client);

void Raylib::init()
{
    Eventloop *e = ModulesGetEventloop();
    e->Subscribe("Update", update, NULL, 1);

    (void)signal(SIGINT, interrupt);
    InitWindow(1080, 720, "Okay");
    SetTargetFPS(60);
}

void Raylib::cleanup()
{
    CloseWindow();
}

static void interrupt
(int sig)
{
    (void)sig;
    ModulesRequestStop();
}

static void update
(Event& e, void *client)
{
    (void)e;
    (void)client;

    if (WindowShouldClose()) {
        ModulesRequestStop();
    }
}

}
