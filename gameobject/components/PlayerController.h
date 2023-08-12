//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include "Component.h"
#include <iostream>

class PlayerController : public Component {
public:
    void init() override {
        std::cout << "PlayerController init" << std::endl;
    }

    void update() override {
        std::cout << "PlayerController update" << std::endl;
    }

    void render() override {
        std::cout << "PlayerController render" << std::endl;
    }
};
