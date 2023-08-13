//
// Created by 06jcu on 8/12/2023.
//

#include "gameobject.h"

void GameObject::init() {
    for (const auto& component : components) {
        component->init();
    }
}

void GameObject::update() {
    for (const auto& component : components) {
        component->update();
    }
}

void GameObject::render() {
    for (const auto& component : components) {
        component->render();
    }
}
