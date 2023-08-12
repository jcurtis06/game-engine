#include "raylib.h"

#include "gameobject/GameObject.h"
#include "gameobject/components/PlayerController.h"
#include "core/Core.h"

int main() {
    const int width = 640;
    const int height = 340;

    InitWindow(width, height, "Game Engine");

    GameObject game_obj;
    game_obj.add_component<PlayerController>();

    Core::add_game_object(game_obj);

    while (!WindowShouldClose()) {
        Core::update();

        BeginDrawing();
        Core::render();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
}
