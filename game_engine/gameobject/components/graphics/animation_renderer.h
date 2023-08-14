//
// Created by 06jcu on 8/14/2023.
//

#pragma once

#include "gameobject/components/component.h"
#include "resources/animation.h"

class AnimationRenderer : public Component {
public:
    Animation animation;

    explicit AnimationRenderer(Animation animation)
        : animation(animation) {}
public:
    void render() override {
        animation.render(WHITE, *position);
    }
    void init() override {}
    void update() override {}
};
