#pragma once

#include <json.hpp>

class Level;

class LevelFormatter {
public:
    static nlohmann::json serialize(Level *level);
    static void deserialize(nlohmann::json levelData, Level *level);
};
