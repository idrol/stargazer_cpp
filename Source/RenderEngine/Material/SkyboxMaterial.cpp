#include "SkyboxMaterial.h"
#include "../Shaders/ShaderManager.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"
#include "../Texture/TexturePromise.h"
#include <GL/glew.h>

SkyboxMaterial::SkyboxMaterial(): Material("SkyboxMaterial", ShaderManager::getShader("skybox")) {}

void SkyboxMaterial::bindTextures() {
    if(skyBoxTexture != nullptr) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture->getTextureID());
    } else if(texturePromise != nullptr) {
        if(texturePromise->isCompleted()) {
            skyBoxTexture = texturePromise->getTexture();
        }
    }
}

Texture *SkyboxMaterial::getSkyBoxTexture() {
    return skyBoxTexture;
}

void SkyboxMaterial::setSkyBoxTexture(Texture *skyBoxTexture) {
    this->skyBoxTexture = skyBoxTexture;
}

void SkyboxMaterial::setSkyBoxTextureWithPath(std::string path) {
    this->skyBoxTexture = TextureManager::getTextureWithPath(path);
}

void SkyboxMaterial::setSkyBoxTextureWithName(std::string name) {
    this->skyBoxTexture = TextureManager::getTextureWithName(name);
}

bool SkyboxMaterial::hasSkyBoxTexture() {
    return skyBoxTexture != nullptr;
}

void SkyboxMaterial::clearSkyBoxTexture() {
    skyBoxTexture = nullptr;
}

void SkyboxMaterial::setSkyBoxTexture(TexturePromise *texturePromise) {
    this->texturePromise = texturePromise;
}

