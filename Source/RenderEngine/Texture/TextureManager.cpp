//
// Created by Idrol on 05-10-2017.
//

#include "TextureManager.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "../../Util/skybox_util.h"
#include <iostream>
#include "../../ResourceManager/ResourceManager.h"
#include "../../Lib/stb_image.h"

std::vector<Texture*> TextureManager::textures;
std::map<std::string, Texture*> TextureManager::textureNameMapping;
std::map<std::string, Texture*> TextureManager::texturePathMapping;
Texture* TextureManager::irradianceTexture = nullptr;
Texture* TextureManager::brdfLUT = nullptr;
Texture* TextureManager::prefilterMap = nullptr;


void TextureManager::registerTextureWithPath(std::string path, Texture *texture) {
    texturePathMapping[path] = texture;
    textures.push_back(texture);
}


void TextureManager::registerTextureWithName(std::string name, Texture *texture) {
    textureNameMapping[name] = texture;
    textures.push_back(texture);
}

std::vector<Texture*> TextureManager::getTextures() {
    return textures;
}

Texture *TextureManager::getTextureWithPath(std::string path) {
    auto it = texturePathMapping.find(path);
    if(it != texturePathMapping.end()) {
        return it->second;
    } else {
        // Texture was not registered load it
        return ResourceManager::getInstance().loadTexture(path);
    }
}

Texture *TextureManager::getTextureWithName(std::string name) {
    auto it = textureNameMapping.find(name);
    if(it != textureNameMapping.end()) {
        return it->second;
    } else {
        std::cout << "Error texture " << name << std::endl;
        return nullptr;
    }
}

void TextureManager::registerDefaults() {

}

void TextureManager::registerTextureWithPath(std::string path) {
    Texture *texture = TextureLoader::getTexture(path);
    if(texture != nullptr) {
        texturePathMapping[path] = texture;
        registerTexture(texture);
    } else {
        std::cout << "Could not load texture " << path << std::endl;
    }
}

void TextureManager::registerTexture(Texture *texture) {
    textures.push_back(texture);
}

void TextureManager::registerHDRTextureWithPath(std::string path) {
    Texture *texture = TextureLoader::getHDRTexture(path);
    if(texture != nullptr) {
        texturePathMapping[path] = texture;
        registerTexture(texture);
    } else {
        std::cout << "Could not load hdr texture " << path << std::endl;
    }
}


void TextureManager::registerHDRTextureWithName(std::string name, std::string path) {
    Texture *texture = TextureLoader::getHDRTexture(path);
    if(texture != nullptr) {
        textureNameMapping[name] = texture;
        registerTexture(texture);
    } else {
        std::cout << "Could not load hdr texture " << path << std::endl;
    }
}

Texture *TextureManager::getIrradianceTexture() {
    return irradianceTexture;
}

void TextureManager::setIrradianceTexture(Texture *texture) {
    irradianceTexture = texture;
}

void TextureManager::setIrradianceTexture(std::string name) {
    setIrradianceTexture(getTextureWithName(name));
}


Texture *TextureManager::getPrefilterMap() {
    return prefilterMap;
}

void TextureManager::setPrefilterMap(Texture *texture) {
    prefilterMap = texture;
}

void TextureManager::setPrefilterMap(std::string name) {
    setPrefilterMap(TextureManager::getTextureWithName(name));
}


Texture *TextureManager::getBRDFLUT() {
    return brdfLUT;
}

void TextureManager::setBRDFLUT(Texture *texture) {
    brdfLUT = texture;
}

void TextureManager::setBRDFLUT(std::string name) {
    setBRDFLUT(TextureManager::getTextureWithName(name));
}

void TextureManager::initialize() {
    stbi_set_flip_vertically_on_load(true);
    registerTextureWithPath("Engine/textures/no_texture.png"); // Create a placeholder texture to be used during texture loading
}
