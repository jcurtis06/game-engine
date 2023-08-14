//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include "component.h"
#include "gameobject/components/physics/kinematic_body.h"
#include <iostream>
#include "raylib.h"

class PlayerController : public Component {
public:
    explicit PlayerController(std::shared_ptr<KinematicBody>& kinematic_body) : kb(kinematic_body) {}

    std::shared_ptr<KinematicBody> kb;

    float max_speed = 200;
    float gravity = 10;
    float jump_force = 200;

    float acceleration = 50;
    float deceleration = 0.2;

    float jump_buffer_time = 15;
    float jump_buffer_counter = 0;

    float coyote_time = 10;
    float coyote_counter = 0;

    void update() override {
        if (!kb->_on_ground) {
            if (coyote_counter > 0) {
                coyote_counter--;
            }

            kb->_velocity.y += gravity;

            if (kb->_velocity.y > 2000) {
                kb->_velocity.y = 2000;
            }
        } else {
            coyote_counter = coyote_time;
        }

        if (IsKeyDown(KEY_RIGHT)) {
            kb->_velocity.x += acceleration;
        } else if (IsKeyDown(KEY_LEFT)) {
            kb->_velocity.x -= acceleration;
        } else {
            kb->_velocity.x = Lerp(kb->_velocity.x, 0, deceleration);
        }

        kb->_velocity.x = Clamp(kb->_velocity.x, -max_speed, max_speed);

        if (IsKeyPressed(KEY_SPACE)) {
            jump_buffer_counter = jump_buffer_time;
        }

        if (jump_buffer_counter > 0) {
            jump_buffer_counter--;
        }

        if (jump_buffer_counter > 0 && coyote_counter > 0) {
            kb->_velocity.y = -jump_force;
            jump_buffer_counter = 0;
            coyote_counter = 0;
        }

        if (IsKeyReleased(KEY_SPACE)) {
            if (kb->_velocity.y < 0) {
                kb->_velocity.y *= 0.5f;
            }
        }

        kb->move();

        position->x = round(position->x);
        position->y = round(position->y);
    }

    void init() override {}

    void render() override {}
};
