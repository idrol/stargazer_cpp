//
// Created by Idrol on 29-09-2017.
//

#include "PBRShader.h"
#include <GLM\glm.hpp>
#include <iostream>

void PBRShader::registerAllUniforms() {
    registerUniform(new Uniform("albedoMap", "sampler2D"));
    registerUniform(new Uniform("normalMap", "sampler2D"));
    registerUniform(new Uniform("metallicMap", "sampler2D"));
    registerUniform(new Uniform("roughnessMap", "sampler2D"));
    registerUniform(new Uniform("aoMap", "sampler2D"));
    registerUniform(new Uniform("irradianceTexture", "samplerCube"));
    registerUniform(new Uniform("prefilterMap", "samplerCube"));
    registerUniform(new Uniform("brdfLUT", "sampler2D"));
    registerUniform(new Uniform("useAlbedoMap", "bool"));
    registerUniform(new Uniform("useNormalMap", "bool"));
    registerUniform(new Uniform("useMetallicMap", "bool"));
    registerUniform(new Uniform("useRoughnessMap", "bool"));
    registerUniform(new Uniform("useAoMap", "bool"));
    registerUniform(new Uniform("useIrradianceTexture", "bool"));
    registerUniform(new Uniform("usePrefilterMap", "bool"));
    registerUniform(new Uniform("useBRDFLUT", "bool"));
    registerUniform(new Uniform("uAlbedo", "vec3"));
    registerUniform(new Uniform("uMetallic", "float"));
    registerUniform(new Uniform("uRoughness", "float"));
    registerUniform(new Uniform("uAo", "float"));
    registerUniform(new Uniform("camPos", "vec3"));
    UniformStruct *lightStruct = new UniformStruct();
    lightStruct->addVariable("position", "vec3");
    lightStruct->addVariable("color", "vec3");
    lightStruct->addVariable("enabled", "bool");
    registerUniform(new Uniform("lights", "Light", lightStruct, MAX_LIGHTS));
}

void PBRShader::loadTextureAddresses() {
    start();
    glActiveTexture(GL_TEXTURE0);
    loadInt("albedoMap", 0);
    glActiveTexture(GL_TEXTURE1);
    loadInt("normalMap", 1);
    glActiveTexture(GL_TEXTURE2);
    loadInt("metallicMap", 2);
    glActiveTexture(GL_TEXTURE3);
    loadInt("roughnessMap", 3);
    glActiveTexture(GL_TEXTURE4);
    loadInt("aoMap", 4);
    glActiveTexture(GL_TEXTURE5);
    loadInt("irradianceTexture", 5);
    glActiveTexture(GL_TEXTURE6);
    loadInt("prefilterMap", 6);
    glActiveTexture(GL_TEXTURE7);
    loadInt("brdfLUT", 7);
}

void PBRShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "uv");
    bindAttribute(2, "normal");
}

void PBRShader::loadLights(std::vector<Light*> lights) {
    start();
    for(int i = 0; i < MAX_LIGHTS; i++) {
        if(i < lights.size()) {
            Light *light = lights[i];
            loadVector3f("lights[" + std::to_string(i) + "].position", light->getPosition());
            loadVector3f("lights[" + std::to_string(i) + "].color", light->getColor()*(float)light->getIntensity());
            loadBool("lights[" + std::to_string(i) + "].enabled", true);
        } else {
            loadVector3f("lights[" + std::to_string(i) + "].position", glm::vec3(0));
            loadVector3f("lights[" + std::to_string(i) + "].color", glm::vec3(0));
            loadBool("lights[" + std::to_string(i) + "].enabled", false);

        }
    }
    stop();
}

void PBRShader::saveCamPos(glm::vec3 camPos) {
    loadVector3f("camPos", camPos);
}

void PBRShader::loadAlbedo(glm::vec3 albedo) {
    loadVector3f("uAlbedo", albedo);
}

void PBRShader::loadMetallic(float metallic) {
    loadFloat("uMetallic", metallic);
}

void PBRShader::loadRoughness(float roughness) {
    loadFloat("uRoughness", roughness);
}

void PBRShader::loadAO(float ao) {
    loadFloat("uAo", ao);
}

void PBRShader::loadUseAlbedoMap(bool flag) {
    loadBool("useAlbedoMap", flag);
}

void PBRShader::loadUseNormalMap(bool flag) {
    loadBool("useNormalMap", flag);
}

void PBRShader::loadUseMetallicMap(bool flag) {
    loadBool("useMetallicMap", flag);
}

void PBRShader::loadUseRoughnessMap(bool flag) {
    loadBool("useRoughnessMap", flag);
}

void PBRShader::loadUseAOMap(bool flag) {
    loadBool("useAoMap", flag);
}

void PBRShader::loadUseIrradianceTexture(bool flag) {
    loadBool("useIrradianceTexture", flag);
}

void PBRShader::loadUsePrefilterMap(bool flag) {
    loadBool("usePrefilterMap", flag);
}

void PBRShader::loadUseBRDFLUT(bool flag) {
    loadBool("useBRDFLUT", flag);
}
