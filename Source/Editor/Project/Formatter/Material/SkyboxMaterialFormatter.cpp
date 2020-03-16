#include "SkyboxMaterialFormatter.h"
#include "../../../../RenderEngine/Material/Material.h"
#include "../../../../RenderEngine/Material/SkyboxMaterial.h"
#include "../../../../RenderEngine/Texture/Texture.h"
#include "../../../../RenderEngine/Texture/TextureManager.h"
#include "../../../../RenderEngine/Model/Mesh.h"
#include "../../../../RenderEngine/RenderEngine.h"

nlohmann::json SkyboxMaterialFormatter::serialize(Material *material) {
    SkyboxMaterial *skyboxMaterial = (SkyboxMaterial*)material;
    std::string skyboxTexture = "";
    if(skyboxMaterial->hasSkyBoxTexture()) {
        skyboxTexture = skyboxMaterial->getSkyBoxTexture()->getPath();
    }

    nlohmann::json materialJson = {
            {"type", skyboxMaterial->getType()},
            {"hasTexture", skyboxMaterial->hasSkyBoxTexture()},
            {"texture", skyboxTexture}
    };
    return materialJson;
}

void SkyboxMaterialFormatter::deserialize(nlohmann::json materialData, Mesh *mesh) {
    SkyboxMaterial *skyboxMaterial = new SkyboxMaterial();
    bool hasTexture = materialData["hasTexture"];
    if(hasTexture) {
        std::map<std::string, TexturePromise*> promises = RenderEngine::getInstance().createPBRCubeMapFromHDR("skybox", materialData["texture"]);
        RenderEngine::getInstance().cycleCommandBuffer();

        skyboxMaterial->setSkyBoxTexture(promises["cubemap"]);
    }
    mesh->setMaterial(skyboxMaterial);
}
