//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <string>
#include <memory>
#include "raymath.h"

class GameObject;

class Component {
public:
    virtual ~Component() = default;

    std::string name;

    std::shared_ptr<GameObject> game_object;
    std::shared_ptr<Vector2> position;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};
