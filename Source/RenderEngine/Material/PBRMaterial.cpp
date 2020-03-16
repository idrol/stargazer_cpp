#include "PBRMaterial.h"
#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"
#include "../Shaders/PBRShader.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"

PBRMaterial::PBRMaterial(): Material("PBRMaterial", ShaderManager::getShader("defaultLitPBR")) {}

void PBRMaterial::apply() {
    shader->start();
    setShaderProperties();
    bindTextures();
}

void PBRMaterial::bindTextures() {
    PBRShader * pbrShader = (PBRShader*) shader;
    if(useAlbedoMap) {
        pbrShader->loadUseAlbedoMap(true);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, albedoMap->getTextureID());
    } else {
        pbrShader->loadUseAlbedoMap(false);
        pbrShader->loadAlbedo(albedoColor);
    }
    if(useNormalMap) {
        pbrShader->loadUseNormalMap(true);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalMap->getTextureID());
    } else {
        pbrShader->loadUseNormalMap(false);
    }
    if(useMetallicMap) {
        pbrShader->loadUseMetallicMap(true);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, metallicMap->getTextureID());
    } else {
        pbrShader->loadUseMetallicMap(false);
        pbrShader->loadMetallic(metallic);
    }
    if(useRoughnessMap) {
        pbrShader->loadUseRoughnessMap(true);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, roughnessMap->getTextureID());
    } else {
        pbrShader->loadUseRoughnessMap(false);
        pbrShader->loadRoughness(roughness);
    }
    if(useAoMap) {
        pbrShader->loadUseAOMap(true);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, aoMap->getTextureID());
    } else {
        pbrShader->loadUseAOMap(false);
        pbrShader->loadAO(ao);
    }
    Texture *irradianceTexture = TextureManager::getIrradianceTexture();
    if(irradianceTexture != nullptr) {
        pbrShader->loadUseIrradianceTexture(true);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceTexture->getTextureID());
    } else {
        pbrShader->loadUseIrradianceTexture(false);
    }
    Texture *prefilterMap = TextureManager::getPrefilterMap();
    if(prefilterMap != nullptr) {
        pbrShader->loadUsePrefilterMap(true);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap->getTextureID());
    } else {
        pbrShader->loadUsePrefilterMap(false);
    }
    Texture *brdfLUT = TextureManager::getBRDFLUT();
    if(brdfLUT != nullptr) {
        pbrShader->loadUseBRDFLUT(true);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, brdfLUT->getTextureID());
    } else {
        pbrShader->loadUseBRDFLUT(false);
    }
}

void PBRMaterial::setShaderProperties() {
    shader->loadTextureAddresses();
}

void PBRMaterial::setAlbedo(glm::vec3 color) {
    useAlbedoMap = false;
    albedoColor = color;
}

void PBRMaterial::setAlbedo(Texture *texture) {
    useAlbedoMap = true;
    albedoMap = texture;
}

glm::vec3 PBRMaterial::getAlbedo() {
	return albedoColor;
}

bool PBRMaterial::hasAlbedoMap() {
	return useAlbedoMap;
}

Texture *PBRMaterial::getAlbedoMap() {
	return albedoMap;
}

void PBRMaterial::setNormalMap(Texture *texture) {
    useNormalMap = true;
    normalMap = texture;
}

bool PBRMaterial::hasNormalMap() {
	return useNormalMap;
}

Texture *PBRMaterial::getNormalMap() {
	return normalMap;
}

void PBRMaterial::setMetallic(float metallic) {
    useMetallicMap = false;
    this->metallic = metallic;
}

void PBRMaterial::setMetallic(Texture *texture) {
    useMetallicMap = true;
    metallicMap = texture;
}

float PBRMaterial::getMetallic() {
	return metallic;
}

bool PBRMaterial::hasMetallicMap() {
	return useMetallicMap;
}

Texture* PBRMaterial::getMetallicMap() {
	return metallicMap;
}

void PBRMaterial::setRoughness(float roughness) {
    useRoughnessMap = false;
    this->roughness = roughness;
}

void PBRMaterial::setRoughness(Texture *texture) {
    useRoughnessMap = true;
    roughnessMap = texture;
}

float PBRMaterial::getRoughness() {
	return roughness;
}

bool PBRMaterial::hasRoughnessMap() {
	return useRoughnessMap;
}

Texture *PBRMaterial::getRoughnessMap() {
	return roughnessMap;
}

void PBRMaterial::setAo(float ao) {
    useAoMap = false;
    this->ao = ao;
}

void PBRMaterial::setAo(Texture *texture) {
    useAoMap = true;
    this->aoMap = texture;
}

void PBRMaterial::setAlbedo(std::string path) {
    useAlbedoMap = true;
    albedoMap = TextureManager::getTextureWithPath(path);
}

void PBRMaterial::setNormalMap(std::string path) {
    useNormalMap = true;
    normalMap = TextureManager::getTextureWithPath(path);
}

void PBRMaterial::setMetallic(std::string path) {
    useMetallicMap = true;
    metallicMap = TextureManager::getTextureWithPath(path);
}

void PBRMaterial::setRoughness(std::string path) {
    useRoughnessMap = true;
    roughnessMap = TextureManager::getTextureWithPath(path);
}

void PBRMaterial::setAo(std::string path) {
    useAoMap = true;
    aoMap = TextureManager::getTextureWithPath(path);
}

void PBRMaterial::clearAlbedoMap() {
    if(hasAlbedoMap()) useAlbedoMap = false;
}

void PBRMaterial::clearNormalMap() {
    if(hasNormalMap()) useNormalMap = false;
}

void PBRMaterial::clearMetallicMap() {
    if(hasMetallicMap()) useMetallicMap = false;
}

void PBRMaterial::clearRoughnessMap() {
    if(hasRoughnessMap()) useRoughnessMap = false;
}
