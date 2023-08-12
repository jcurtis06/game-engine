//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <string>

class GameObject;

class Component {
public:
    virtual ~Component() = default;

    std::string name;
    GameObject* game_object;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};
