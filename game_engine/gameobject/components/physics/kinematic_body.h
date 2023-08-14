//
// Created by 06jcu on 8/13/2023.
//

#pragma once

#include "gameobject/components/component.h"
#include "raylib.h"
#include "core.h"

class KinematicBody : public Component {
public:
    KinematicBody(int width, int height)
        : _width(width), _height(height) {}

    int _width, _height;
    Vector2 _velocity;
    bool _on_ground = false;

    void move() {
        Vector2 old_pos = *position;
        Vector2 new_pos = {position->x + _velocity.x * GetFrameTime(), position->y + _velocity.y * GetFrameTime()};

        Rectangle horizontal = create_swept_box(old_pos, {new_pos.x, old_pos.y});

        _on_ground = false;

        for (auto& rect : Core::colliders) {
            if (CheckCollisionRecs(rect, horizontal)) {
                if (_velocity.x > 0) {
                    new_pos.x = rect.x - (float) _width;
                } else {
                    new_pos.x = rect.x + rect.width;
                }
            }
        }

        Rectangle vertical = create_swept_box(old_pos, {old_pos.x, new_pos.y});

        for (auto& rect : Core::colliders) {
            if (CheckCollisionRecs(rect, vertical)) {
                if (_velocity.y > 0) {
                    new_pos.y = rect.y - (float) _height;
                    _on_ground = true;
                } else {
                    new_pos.y = rect.y + rect.height;
                }
            }
        }

        position->x = new_pos.x;
        position->y = new_pos.y;
    }

    void init() override {
    }

    void update() override {

    }

    void render() override {

    }
private:
    Rectangle create_swept_box(Vector2 from, Vector2 to) {
        float x = std::min(from.x, to.x);
        float y = std::min(from.y, to.y);

        float width = std::abs(to.x - from.x) + (float) _width;
        float height = std::abs(to.y - from.y) + (float) _height;

        return { x, y, width, height };
    }
};
