//
// Created by 06jcu on 8/12/2023.
//

#pragma once

#include <string>
#include "nlohmann/json.hpp"

struct Tile {
    int x, y;
    int variant;
    std::string type;

    nlohmann::json to_json() {
        return {
            {"x", x},
            {"y", y},
            {"variant", variant},
            {"type", type}
        };
    }

    static Tile from_json(nlohmann::json json) {
        Tile tile;
        tile.x = json["x"];
        tile.y = json["y"];
        tile.variant = json["variant"];
        tile.type = json["type"];
        return tile;
    }
};
