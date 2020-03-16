//
// Created by Idrol on 12-10-2017.
//

#include "PrefilterMaterial.h"
#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"
#include "../Texture/TextureManager.h"
#include "../Texture/Texture.h"

PrefilterMaterial::PrefilterMaterial(): Material("PrefilterMaterial", ShaderManager::getShader("prefilterShader")) {}

void PrefilterMaterial::apply() {
    shader->start();
    bindTextures();
}

void PrefilterMaterial::bindTextures() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, enviormentMap->getTextureID());
    shader->loadFloat("roughness", roughness);
}

void PrefilterMaterial::setEnviormentMap(Texture *texture) {
    enviormentMap = texture;
}

void PrefilterMaterial::setEnviormentMap(std::string name) {
    setEnviormentMap(TextureManager::getTextureWithName(name));
}

void PrefilterMaterial::setRoughness(float roughness) {
    this->roughness = roughness;
}
