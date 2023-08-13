#include "raylib.h"

#include "gameobject/gameobject.h"
#include "core.h"
#include "gameobject/components/graphics/tilemaprenderer.h"
#include <string>

int main() {
    const int width = 640;
    const int height = 340;

    InitWindow(width, height, "Game Engine");

    std::map<std::string, Texture2D> textures;
    textures["tiles"] = LoadTexture("assets/tiles.png");

    auto tilemap = std::make_shared<GameObject>();
    tilemap->add_component<TilemapRenderer>(16, textures);
    tilemap->get_component<TilemapRenderer>()->load("assets/tilemap.json");

    Core::add_game_object(tilemap);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Core::update();

        BeginDrawing();
        ClearBackground(WHITE);

        Core::render();
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}
