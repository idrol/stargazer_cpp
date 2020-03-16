#include "GenerateIrradianceMapFromCubeMap.h"
#include "../Texture/TextureManager.h"
#include "../Texture/TextureLoader.h"
#include "../Texture/TexturePromise.h"
#include "../Texture/Texture.h"

GenerateIrradianceMapFromCubeMap::GenerateIrradianceMapFromCubeMap(std::string irradianceName, std::string cubeMapName,
                                                                   Model *cubeModel, std::string path) {
    this->irradianceName = irradianceName;
    this->cubeMapName = cubeMapName;
    this->cubeModel = cubeModel;
    this->path = path;
}

void GenerateIrradianceMapFromCubeMap::execute() {
    Texture *irradianceTexture = TextureLoader::generateIrradianceMapFromCubeMap(
            TextureManager::getTextureWithName(cubeMapName), cubeModel);
    irradianceTexture->setPath(path);
    if(texturePromise) {
        texturePromise->completePromise(irradianceTexture);
    }
    TextureManager::registerTextureWithName(irradianceName, irradianceTexture);
}

TexturePromise *GenerateIrradianceMapFromCubeMap::getTexturePromise() {
    if(texturePromise == nullptr) {
        texturePromise = new TexturePromise();
    }
    return texturePromise;
}
