//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <typeinfo>
#include <type_traits>
#include <vector>
#include <memory>
#include <algorithm>
#include "raymath.h"
#include "components/component.h"

struct GameObject {
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<Vector2> position = std::make_shared<Vector2>();

    template<typename T, typename... Args>
    std::shared_ptr<T> add_component(Args... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        auto component = std::make_shared<T>(args...);

        component->game_object = std::make_shared<GameObject>(*this);
        component->position = position;

        components.push_back(std::static_pointer_cast<Component>(component));
        return component;
    }

    template<typename T>
    void remove_component() {
        auto it = std::remove_if(components.begin(), components.end(), [](const std::shared_ptr<Component>& component) {
             return dynamic_cast<T*>(component.get()) != nullptr;
        });

        components.erase(it, components.end());
    }

    template<typename T>
    std::shared_ptr<T> get_component() {
        for (const auto& component : components) {
            if (typeid(*component) == typeid(T)) {
                return std::dynamic_pointer_cast<T>(component);
            }
        }
        return nullptr;
    }

    void init();

    void update();

    void render();
};
