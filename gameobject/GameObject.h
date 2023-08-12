//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <typeinfo>
#include <type_traits>
#include <vector>
#include <memory>
#include "components/Component.h"

struct GameObject {
    std::vector<std::shared_ptr<Component>> components;

    template<typename T, typename... Args>
    std::shared_ptr<T> add_component(Args... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        auto component = std::make_shared<T>(args...);
        components.push_back(std::static_pointer_cast<Component>(component));
        return component;
    }

    template<typename T>
    void remove_component() {
        for (auto it = components.begin(); it != components.end(); ++it) {
            if (typeid(*it) == typeid(T)) {
                components.erase(it);
                return;
            }
        }
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

    void init() {
        for (const auto& component : components) {
            component->init();
        }
    }

    void update() {
        for (const auto& component : components) {
            component->update();
        }
    }

    void render() {
        for (const auto& component : components) {
            component->render();
        }
    }
};
