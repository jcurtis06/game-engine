//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "../gameobject/GameObject.h"

class Core {
public:
    static std::vector<std::shared_ptr<GameObject>> game_objects;

    static void add_game_object(GameObject& game_object) {
        game_objects.push_back(std::make_shared<GameObject>(game_object));
        game_object.init();
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
