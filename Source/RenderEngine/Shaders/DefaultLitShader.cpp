//
// Created by Idrol on 29-09-2017.
//

#include "DefaultLitShader.h"

void DefaultLitShader::registerAllUniforms() {
    DefaultUnlitShader::registerAllUniforms();
    UniformStruct *lightStruct = new UniformStruct();
    lightStruct->addVariable("position", "vec3");
    lightStruct->addVariable("color", "vec3");
   // lightStruct->addVariable("attenuation", "vec3");
    lightStruct->addVariable("enabled", "bool");
    registerUniform(new Uniform("lights", "Light", lightStruct, MAX_LIGHTS));
    registerUniform(new Uniform("skyColor", "vec3"));
    registerUniform(new Uniform("specularIntensity", "float"));
    registerUniform(new Uniform("specularPower", "float"));
    registerUniform(new Uniform("roughness", "float"));
    registerUniform(new Uniform("reflectivity", "float"));
    registerUniform(new Uniform("reflectionColor", "vec3"));
    registerUniform(new Uniform("cameraPosition", "vec3"));
    registerUniform(new Uniform("cubeSampler", "samplerCube"));
    registerUniform(new Uniform("useNormalMap", "bool"));
    registerUniform(new Uniform("normalMapSampler", "sampler2D"));
    registerUniform(new Uniform("useSpecularMap", "bool"));
    registerUniform(new Uniform("specularMapSampler", "sampler2D"));
}

void DefaultLitShader::loadLights(std::vector<Light*> lights) {
    start();
    for(int i = 0; i < MAX_LIGHTS; i++) {
        if(i < lights.size()) {
            Light *light = lights[i];
            loadVector3f("lights[" + std::to_string(i) + "].position", light->getPosition());
            loadVector3f("lights[" + std::to_string(i) + "].color", light->getColor());
           // loadVector3f("lights[" + std::to_string(i) + "].attenuation", light->getAttenuation());
            loadBool("lights[" + std::to_string(i) + "].enabled", true);
        } else {
            loadVector3f("lights[" + std::to_string(i) + "].position", glm::vec3(0));
            loadVector3f("lights[" + std::to_string(i) + "].color", glm::vec3(0));
           // loadVector3f("lights[" + std::to_string(i) + "].attenuation", glm::vec3(1, 0, 0));
            loadBool("lights[" + std::to_string(i) + "].enabled", false);

        }
    }
    stop();
}

void DefaultLitShader::loadTextureAddresses() {
    start();
    loadInt("textureSampler", 0);
    loadInt("cubeSampler", 1);
    loadInt("normalMapSampler", 2);
    loadInt("specularMapSampler", 3);
    stop();
}

void DefaultLitShader::loadUseNormal(bool useNormal) {
    loadBool("useNormalMap", useNormal);
}

void DefaultLitShader::loadUseSpecular(bool useSpecular) {
    loadBool("useSpecularMap", useSpecular);
}

void DefaultLitShader::loadSkyColor(glm::vec3 color) {
    loadVector3f("skyColor", color);
}

void DefaultLitShader::loadSpecularInensity(float specular) {
    loadFloat("specularIntensity", specular);
}

void DefaultLitShader::loadSpecularPower(float specularPower) {
    loadFloat("specularPower", specularPower);
}

void DefaultLitShader::loadRoughness(float roughness) {
    loadFloat("roughness", roughness);
}

void DefaultLitShader::loadReflectivity(float reflectivity) {
    loadFloat("reflectivity", reflectivity);
}

void DefaultLitShader::loadReflectionColor(glm::vec3 color) {
    loadVector3f("reflectionColor", color);
}

void DefaultLitShader::loadCameraPosition(glm::vec3 position) {
    loadVector3f("cameraPosition", position);
}