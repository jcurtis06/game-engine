//
// Created by 06jcu on 8/13/2023.
//

#include <map>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include "tile.h"

struct Tilemap {
    Tilemap(int tile_size,  std::map<std::string, Texture2D> tile_textures)
            : _tile_size(tile_size), _tile_textures(std::move(tile_textures)) {}

    Tilemap(int tile_size, std::map<std::string, Texture2D> tile_textures, const std::string &path)
            : _tile_size(tile_size), _tile_textures(std::move(tile_textures)) {
        load(path);
    }

    int _tile_size;

    std::map<std::string, Texture2D> _tile_textures;
    std::vector<Tile> _loaded_tiles;

    void load(const std::string &path) {
        std::ifstream file(path);

        if (!file.is_open()) {
            std::cout << "Failed to load tilemap: " << path << std::endl;
            return;
        }

        nlohmann::json json;
        file >> json;
        file.close();

        _loaded_tiles.clear();

        for (const auto &item: json) {
            _loaded_tiles.push_back(Tile::from_json(item));
        }

        std::cout << "Loaded " << _loaded_tiles.size() << " tiles" << std::endl;
    }
};