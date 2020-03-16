//
// Created by Idrol on 11-10-2017.
//

#include "ConvertHDRToCubeMap.h"
#include "../Texture/TextureManager.h"
#include "../Texture/TextureLoader.h"
#include "../Texture/TexturePromise.h"
#include "../Texture/Texture.h"
#include "../Model/Model.h"
#include <iostream>

ConvertHDRToCubeMap::ConvertHDRToCubeMap(std::string cubeMapName, std::string hdrName, Model *cubeModel, std::string path) {
    this->cubeMapName = cubeMapName;
    this->hdrName = hdrName;
    this->cubeModel = cubeModel;
    this->path = path;
}

void ConvertHDRToCubeMap::execute() {
    Texture *cubeMap = TextureLoader::convertHDRTextureToCubeMap(TextureManager::getTextureWithName(hdrName), cubeModel);
    cubeMap->setPath(path);
    if(texturePromise) {
        texturePromise->completePromise(cubeMap);
    }
    TextureManager::registerTextureWithName(cubeMapName, cubeMap);
}

TexturePromise *ConvertHDRToCubeMap::getTexturePromise() {
    if(texturePromise == nullptr) {
        texturePromise = new TexturePromise();
    }
    return texturePromise;
}
