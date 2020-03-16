#pragma once

#include <string>
#include <map>
#include <json.hpp>

class MaterialFormatter;
class Material;
class Mesh;

class MaterialFormatManager {
public:
    MaterialFormatManager();
    nlohmann::json serialize(Material *material);
    void deserialize(nlohmann::json materialData, Mesh *mesh);

private:
    void registerMaterialFormatter(std::string formatterName, MaterialFormatter *materialFormatter);
    std::map<std::string, MaterialFormatter*> materialFormatters;
};


