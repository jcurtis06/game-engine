//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include "gameobject/gameobject.h"

class Core {
public:
    int resolution_width = 160;
    int resolution_height = 90;

    int screen_width = 800;
    int screen_height = 450;

    const float res_ratio = (float) screen_width / (float) resolution_width;
public:
    static std::vector<std::shared_ptr<GameObject>> game_objects;
    static std::vector<Rectangle> colliders;

    static std::shared_ptr<Camera2D> current_camera;

    static void add_game_object(const std::shared_ptr<GameObject>& game_object) {
        game_objects.emplace_back(game_object);
        game_objects.back()->init();
    }

    static void update() {
        for (const auto& game_object : game_objects) {
            game_object->update();
        }
    }

    static void render() {
        BeginMode2D(*current_camera);
        for (const auto& game_object : game_objects) {
            game_object->render();
        }
        EndMode2D();
    }
private:
    Camera2D _screen_camera = {0};
    RenderTexture2D target = LoadRenderTexture(resolution_width, resolution_height);
};
