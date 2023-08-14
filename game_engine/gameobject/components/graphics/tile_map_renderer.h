//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <iostream>
#include "nlohmann/json.hpp"
#include "raylib.h"

#include "gameobject/components/component.h"
#include "resources/tilemap.h"

class TileMapRenderer : public Component {
public:
    explicit TileMapRenderer(Tilemap &tile_map)
            : _tile_map(tile_map) {}

    Tilemap _tile_map;
public:
    void render() override {
        for (const auto &tile: _tile_map._loaded_tiles) {
            if (_tile_map._tile_textures.find(tile.type) == _tile_map._tile_textures.end()) {
                std::cerr << "Tile type " << tile.type << " not found in tile textures" << std::endl;
                continue;
            }

            const Texture2D &texture = _tile_map._tile_textures.at(tile.type);
            const int t_size = _tile_map._tile_size;

            int h_tiles = texture.width / _tile_map._tile_size;

            Rectangle source{
                (float)(t_size * (tile.variant % h_tiles)),
                (float)(t_size * (tile.variant / h_tiles)),
                (float)t_size, (float)t_size };

            DrawTextureRec(texture, source, Vector2{ (float)tile.x, (float)(tile.y) }, WHITE);
        }
    }

    void update() override {}

    void init() override {}
};
