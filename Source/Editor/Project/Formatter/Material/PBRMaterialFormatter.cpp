#include "PBRMaterialFormatter.h"
#include "../../../../RenderEngine/Material/Material.h"
#include "../../../../RenderEngine/Material/PBRMaterial.h"
#include "../../../../RenderEngine/Texture/Texture.h"
#include "../../../../RenderEngine/Texture/TextureManager.h"
#include "../../../../RenderEngine/Model/Mesh.h"

nlohmann::json PBRMaterialFormatter::serialize(Material *material) {
    PBRMaterial *pbrMaterial = (PBRMaterial*)material;
    std::string albedoTexture = "";
    if(pbrMaterial->hasAlbedoMap()) {
        albedoTexture = pbrMaterial->getAlbedoMap()->getPath();
    }
    std::string roughnessTexture = "";
    if(pbrMaterial->hasRoughnessMap()) {
        roughnessTexture = pbrMaterial->getRoughnessMap()->getPath();
    }
    std::string metallicTexture = "";
    if(pbrMaterial->hasMetallicMap()) {
        metallicTexture = pbrMaterial->getMetallicMap()->getPath();
    }
    std::string normalTexture = "";
    if(pbrMaterial->hasNormalMap()) {
        normalTexture = pbrMaterial->getNormalMap()->getPath();
    }
    nlohmann::json materialJson = {
            {"type", pbrMaterial->getType()},
            {"albedoUseTexture", pbrMaterial->hasAlbedoMap()},
            {"albedoTexture", albedoTexture},
            {"albedo", {pbrMaterial->getAlbedo().x, pbrMaterial->getAlbedo().y, pbrMaterial->getAlbedo().z}},
            {"roughnessUseTexture", pbrMaterial->hasRoughnessMap()},
            {"roughnessTexture", roughnessTexture},
            {"roughness", pbrMaterial->getRoughness()},
            {"metallicUseTexture", pbrMaterial->hasMetallicMap()},
            {"metallicTexture", metallicTexture},
            {"metallic", pbrMaterial->getMetallic()},
            {"normalUseTexture", pbrMaterial->hasNormalMap()},
            {"normalTexture", normalTexture}
    };
    return materialJson;
}

void PBRMaterialFormatter::deserialize(nlohmann::json materialData, Mesh *mesh) {
    PBRMaterial *material = new PBRMaterial();
    bool useAlbedo = materialData["albedoUseTexture"];
    bool useRoughness = materialData["roughnessUseTexture"];
    bool useMetallic = materialData["metallicUseTexture"];
    bool useNormal = materialData["normalUseTexture"];
    if(useAlbedo) {
        material->setAlbedo(TextureManager::getTextureWithPath(materialData["albedoTexture"]));
    } else {
        material->setAlbedo(glm::vec3(materialData["albedo"][0], materialData["albedo"][1], materialData["albedo"][2]));
    }
    if(useRoughness) {
        material->setRoughness(TextureManager::getTextureWithPath(materialData["roughnessTexture"]));
    } else {
        material->setRoughness(materialData["roughness"].get<float>());
    }
    if(useMetallic) {
        material->setMetallic(TextureManager::getTextureWithPath(materialData["metallicTexture"]));
    } else {
        material->setMetallic(materialData["metallic"].get<float>());
    }
    if(useNormal) {
        material->setNormalMap(TextureManager::getTextureWithPath(materialData["normalTexture"]));
    }
    mesh->setMaterial(material);
}
