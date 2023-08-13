//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include "../component.h"
#include "nlohmann/json.hpp"
#include "raylib.h"
#include "resources/tile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class TilemapRenderer : public Component {
public:
    TilemapRenderer(int size, std::map<std::string, Texture2D> textures)
            : size(size), textures(textures) {}

    int size;
    std::map<std::string, Texture2D> textures;
public:
    void load(const std::string &path) {
        std::ifstream file(path);

        if (!file.is_open()) return;

        nlohmann::json json;
        file >> json;
        file.close();

        tiles.clear();

        for (const auto &item: json) {
            tiles.push_back(Tile::from_json(item));
        }

        std::cout << "Loaded " << tiles.size() << " tiles" << std::endl;
    }

    void render() override {
        for (const auto &tile: tiles) {
            const auto &texture = textures["tiles"];

            int h_tiles = texture.width / size;
            int v_tiles = texture.height / size;

            Rectangle source{
                (float)(size * (tile.variant % h_tiles)),
                (float)(size * (tile.variant / v_tiles)),
                (float)size, (float)size };

            DrawTextureRec(texture, source, Vector2{ (float)tile.x, (float)(tile.y) }, WHITE);
        }
    }

    void update() override {}

    void init() override {}

private:
    std::vector<Tile> tiles;
};
