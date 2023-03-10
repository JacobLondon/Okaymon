#include <utils/modules.hpp>
#include "mod.hpp"
#include <signal.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

namespace Okay {

#define ASSETS_DIR "assets"

static void interrupt(int sig);
static void update(Event& e, void *client);

static FilePathList assets;

static void load_pngs_into_slots()
{
    Assert(DirectoryExists(ASSETS_DIR));

    assets = LoadDirectoryFiles(ASSETS_DIR);

    for (size_t i = 0; i < assets.count; i++) {
        char *path = assets.paths[i];
        Assert(path != NULL);
        if (!IsFileExtension(path, ".png")) continue;

        // save all pngs into slots by path name
        Texture2D texture = LoadTexture(path);
        auto texturep = (Texture2D *)MemAlloc(sizeof(texture));
        Assert(texturep != NULL);
        memcpy(texturep, &texture, sizeof(*texturep));

        ModulesSlotsInsert(path, texturep, [](void *_a){
            auto a = (Texture2D *)_a;
            UnloadTexture(*a);
            MemFree(a);
        });
    }
}

void ModRaylib::init()
{
    ModulesTimeoutSubscribe("ModRaylib.Update", update, NULL, 1);

    InitWindow(1080, 720, "Okay");
    SetTargetFPS(60);

    // must be after Raylib is initialized
    load_pngs_into_slots();

    (void)signal(SIGINT, interrupt);
}

void ModRaylib::cleanup()
{
    UnloadDirectoryFiles(assets);
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
