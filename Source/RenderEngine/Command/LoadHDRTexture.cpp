//
// Created by Idrol on 10-10-2017.
//

#include "LoadHDRTexture.h"
#include "../Texture/TextureManager.h"
#include "../Texture/TexturePromise.h"

LoadHDRTexture::LoadHDRTexture(std::string path) {
    this->path = path;
}

void LoadHDRTexture::execute() {
    if(name.empty()) {
        TextureManager::registerHDRTextureWithPath(path);
        if(texturePromise != nullptr) {
            texturePromise->completePromise(TextureManager::getTextureWithPath(path));
        }
    } else {
        TextureManager::registerHDRTextureWithName(name, path);
        if(texturePromise != nullptr) {
            texturePromise->completePromise(TextureManager::getTextureWithName(name));
        }
    }
}

LoadHDRTexture::LoadHDRTexture(std::string name, std::string path): LoadHDRTexture(path) {
    this->name = name;
}

TexturePromise *LoadHDRTexture::getTexturePromise() {
    if(texturePromise == nullptr) {
        texturePromise = new TexturePromise();
    }
    return texturePromise;
}
