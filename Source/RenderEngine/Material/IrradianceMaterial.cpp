//
// Created by Idrol on 12-10-2017.
//

#include "IrradianceMaterial.h"
#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"

IrradianceMaterial::IrradianceMaterial(): Material("IrradianceMaterial", ShaderManager::getShader("irradianceShader")) {}

void IrradianceMaterial::apply() {
    shader->start();
    bindTextures();
}

void IrradianceMaterial::bindTextures() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, enviormentMap->getTextureID());
}

void IrradianceMaterial::setEnviormentMap(Texture *texture) {
    enviormentMap = texture;
}

void IrradianceMaterial::setEnviormentMap(std::string name) {
    setEnviormentMap(TextureManager::getTextureWithName(name));
}
