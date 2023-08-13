//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "../gameobject/gameobject.h"

class Core {
public:
    static std::vector<std::shared_ptr<GameObject>> game_objects;

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
        for (const auto& game_object : game_objects) {
            game_object->render();
        }
    }
};
