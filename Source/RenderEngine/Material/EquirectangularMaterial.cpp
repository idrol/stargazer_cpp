#include "EquirectangularMaterial.h"
#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"

EquirectangularMaterial::EquirectangularMaterial(): Material("EquirectangularMaterial", ShaderManager::getShader("equirectangularShader")) {}

void EquirectangularMaterial::apply() {
    shader->start();
    bindTextures();
}

void EquirectangularMaterial::bindTextures() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, equirectangularTexture->getTextureID());
}

void EquirectangularMaterial::setEquirectangularTexture(Texture *texture) {
    equirectangularTexture = texture;
}

void EquirectangularMaterial::setEquirectangularTexture(std::string name) {
    setEquirectangularTexture(TextureManager::getTextureWithName(name));
}
