//
// Created by Idrol on 29-09-2017.
//

#include "DefaultUnlitShader.h"
#include <iostream>

void DefaultUnlitShader::registerAllUniforms() {
    std::cout << "Registering all uniforms" << std::endl;
    registerUniform(new Uniform("useTexture", "bool"));
    registerUniform(new Uniform("diffuseColor", "vec3"));
    registerUniform(new Uniform("textureSampler", "sampler2D"));
}

void DefaultUnlitShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "uv");
    bindAttribute(2, "normal");
    bindAttribute(3, "tangent");
}

void DefaultUnlitShader::loadUseTexture(bool useTexture) {
    loadBool("useTexture", static_cast<GLboolean>(useTexture));
}

void DefaultUnlitShader::loadDiffuseColor(glm::vec3 color) {
    loadVector3f("diffuseColor", color);
}
