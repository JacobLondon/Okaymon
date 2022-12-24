#include "mod.hpp"
#include "writer.hpp"
#include <utils/time.hpp>

#include <queue>
#include <vector>

namespace Okay {

static void update(Event& e, void *client);
static void notify(void *client);
static void pause();
static void resume();

static std::queue<std::string> queue;
static int state;
static Writer writer;

void ModMessages::init()
{
    Assert(ModulesLoaded("ModBattle"));
    Assert(ModulesLoaded("ModWorld"));

    ModulesTimeoutSubscribe("ModMessages.Update", update, NULL, 0);
    ModulesNexusSubscribe("ModMessages.Notify", notify);
}

void ModMessages::cleanup()
{
    while (queue.size() > 0) {
        queue.pop();
    }

    state = 0;
    writer.Clear();
}

static void write_now()
{
    const char *c = writer.Get();

    Rectangle rect = Rectangle{0, GetScreenHeight() * 0.7f, (float)GetScreenWidth(), GetScreenHeight() * 0.3f};

    BeginDrawing();
    DrawRectangleRec(rect, LIGHTGRAY);
    DrawText(c, 0, GetScreenHeight() * 0.7, 24, BLACK);
    EndDrawing();
}

static void update
(Event& e, void *client)
{
    (void)e;
    (void)client;

    if (queue.empty()) {
        return;
    }

    static size_t wait;
    switch (state)
    {
    case 0:
        writer.Begin(queue.back());

        pause();
        state = 1;
        break;
    case 1:
    {
        writer.Next();
        write_now();

        if (writer.Done()) {
            state = 2;
        }

        wait = TimeNowMillis();
        break;
    }
    case 2:
    {
        size_t now = TimeNowMillis();
        if ((now - wait) >= 1000) {
            state = 3;
        }

        write_now();
        break;
    }
    case 3:
        write_now();
        queue.pop();
        resume();
        state = 0;
        break;
    default:
        break;
    }
}

static void notify
(void *client)
{
    auto message = (const char *)client;
    queue.emplace(message);
}

static void pause()
{
    ModulesPause("ModBattle.Update");
    ModulesPause("ModWorld.Update");
}

static void resume()
{
    ModulesResume("ModBattle.Update");
    ModulesResume("ModWorld.Update");
}

}