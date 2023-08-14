//
// Created by 06jcu on 8/13/2023.
//

#pragma once

#include "gameobject/components/component.h"
#include "core.h"
#include <string>

class TileMapCollider : public Component {
public:
    explicit TileMapCollider(Tilemap &tile_map)
    : _tile_map(tile_map) {}

    Tilemap _tile_map;
    std::vector<std::string> _collide_types;
public:
    void init() override {
        for (const auto &tile: _tile_map._loaded_tiles) {
            if (std::find(_collide_types.begin(), _collide_types.end(), tile.type) != _collide_types.end()) {
                Core::colliders.emplace_back(Rectangle{
                    (float)(tile.x),
                    (float)(tile.y),
                    (float)_tile_map._tile_size,
                    (float)_tile_map._tile_size
                });
            }
        }
    }

    void update() override {}

    void render() override {}
};
