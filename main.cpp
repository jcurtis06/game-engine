#include "raylib.h"

#include "gameobject/gameobject.h"
#include "core.h"
#include "gameobject/components/graphics/tile_map_renderer.h"
#include "gameobject/components/physics/tile_map_collider.h"
#include "gameobject/components/playercontroller.h"
#include "gameobject/components/physics/kinematic_body.h"
#include "gameobject/components/graphics/animation_renderer.h"
#include <string>

int main() {
    const int width = 640;
    const int height = 340;

    InitWindow(width, height, "Game Engine");

    std::map<std::string, Texture2D> textures;
    textures["tiles"] = LoadTexture("assets/tiles.png");
    textures["player_idle"] = LoadTexture("assets/player_idle.png");

    auto tile_map = std::make_shared<GameObject>();

    tile_map->add_component<TileMapRenderer>(Tilemap{8, textures, "assets/tilemap2.json" });
    tile_map->add_component<TileMapCollider>(Tilemap{8, textures, "assets/tilemap2.json" });

    tile_map->get_component<TileMapCollider>()->_collide_types.emplace_back("tiles");

    Core::add_game_object(tile_map);

    auto player = std::make_shared<GameObject>();
    player->position->x = 5;
    player->position->y = 80;

    player->add_component<KinematicBody>(9, 9);
    player->add_component<PlayerController>(player->get_component<KinematicBody>());

    Animation idle_animation = Animation{ textures["player_idle"], 4, 1, 0, 3, 0.1f };

    player->add_component<AnimationRenderer>(idle_animation);

    Core::add_game_object(player);

    Core::current_camera = std::make_shared<Camera2D>();
    Core::current_camera->zoom = 3;
    Core::current_camera->offset = {width / 2, height / 2};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Core::update();
        Core::current_camera->target = *player->position;

        std::cout << Core::current_camera->target.x << std::endl;

        BeginDrawing();
        ClearBackground(Color {24, 20, 37, 255});

        Core::render();
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}
