//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include "../component.h"
#include "raylib.h"
#include <iostream>

class SpriteRenderer : public Component {
public:
    explicit SpriteRenderer(Texture2D texture, Color tint = WHITE)
        : texture(texture), tint(tint) {}

    Texture2D texture;
    Color tint = WHITE;

    Vector2 offset = {0, 0};

    void init() override {}

    void update() override {
        std::cout << position->x << ", " << position->y << std::endl;
    }

    void render() override {
        DrawTexture(texture, (int)(position->x + offset.x), (int)(position->y + offset.y), tint);
    }
};
