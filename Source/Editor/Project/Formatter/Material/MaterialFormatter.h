#pragma once

#include <json.hpp>

class Material;
class Mesh;

class MaterialFormatter {
public:
    virtual nlohmann::json serialize(Material *material) {
        return nlohmann::json {};
    };
    virtual void deserialize(nlohmann::json materialData, Mesh *mesh) {};
};


