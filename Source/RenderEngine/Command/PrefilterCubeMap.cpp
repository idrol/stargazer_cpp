#include "PrefilterCubeMap.h"
#include "../Texture/TextureLoader.h"
#include "../Texture/TextureManager.h"
#include "../Texture/TexturePromise.h"
#include "../Texture/Texture.h"

PrefilterCubeMap::PrefilterCubeMap(std::string prefilterName, std::string cubeMapName, Model *cubeModel, std::string path) {
    this->prefilterName = prefilterName;
    this->cubeMapName = cubeMapName;
    this->cubeModel = cubeModel;
    this->path = path;
}

void PrefilterCubeMap::execute() {
    Texture *prefilter = TextureLoader::prefilterCubeMap(TextureManager::getTextureWithName(cubeMapName), cubeModel);
    prefilter->setPath(path);
    if(texturePromise != nullptr) {
        texturePromise->completePromise(prefilter);
    }
    TextureManager::registerTextureWithName(prefilterName, prefilter);
}

TexturePromise *PrefilterCubeMap::getTexturePromise() {
    if(texturePromise == nullptr) {
        texturePromise = new TexturePromise();
    }
    return texturePromise;
}
