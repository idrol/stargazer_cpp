#include "MaterialFormatManager.h"
#include "Material/PBRMaterialFormatter.h"
#include "Material/SkyboxMaterialFormatter.h"
#include "../../../RenderEngine/Material/Material.h"
#include <iostream>

void MaterialFormatManager::registerMaterialFormatter(std::string formatterName, MaterialFormatter *materialFormatter) {
    materialFormatters[formatterName] = materialFormatter;
}

MaterialFormatManager::MaterialFormatManager() {
    registerMaterialFormatter("PBRMaterial", new PBRMaterialFormatter());
    registerMaterialFormatter("SkyboxMaterial", new SkyboxMaterialFormatter());
}

nlohmann::json MaterialFormatManager::serialize(Material *material) {
    auto it = materialFormatters.find(material->getType());
    if(it == materialFormatters.end()) {
        std::cout << "Material " << material->getType() << " has no registered formatter and will not be saved." << std::endl;
        return nlohmann::json();
    }
    return it->second->serialize(material);
}

void MaterialFormatManager::deserialize(nlohmann::json materialData, Mesh *mesh) {
    std::string type = materialData["type"];
    auto it = materialFormatters.find(type);
    if(it == materialFormatters.end()) {
        std::cout << "Material " << type << " has no registered formatter and will not be loaded." << std::endl;
        return;
    }
    return it->second->deserialize(materialData, mesh);
}
