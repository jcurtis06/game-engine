//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include "component.h"
#include <iostream>

class PlayerController : public Component {
public:
    void init() override {
    }

    void update() override {
        position->x += 1;
    }

    void render() override {
        DrawRectangle((int)position->x, (int)position->y, 50, 50, RED);
    }
};
