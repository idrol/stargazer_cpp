//
// Created by Idrol on 02-10-2017.
//

#include "UnlitMaterial.h"
#include "../Shaders/Shader.h"
#include "../Shaders/DefaultUnlitShader.h"
#include "../Shaders/ShaderManager.h"
#include "../Texture/Texture.h"

UnlitMaterial::UnlitMaterial(): Material("UnlitMaterial", ShaderManager::getShader("defaultUnlit")) {}

void UnlitMaterial::apply() {
    shader->start();
    bindTextures();
}

void UnlitMaterial::bindTextures() {
    DefaultUnlitShader *unlitShader = (DefaultUnlitShader*) shader;
    if(useTexture) {
        unlitShader->loadUseTexture(true);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture->getTextureID());
    } else {
        unlitShader->loadUseTexture(false);
        unlitShader->loadDiffuseColor(diffuseColor);
    }
}

void UnlitMaterial::setDiffuseColor(glm::vec3 color) {
    this->useTexture = false;
    this->diffuseColor = color;
}
