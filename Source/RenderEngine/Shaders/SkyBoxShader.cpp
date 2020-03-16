//
// Created by Idrol on 29-09-2017.
//

#include "SkyBoxShader.h"

void SkyBoxShader::registerAllUniforms() {
    DefaultUnlitShader::registerAllUniforms();
    unregisterUniform("textureSampler");
    registerUniform(new Uniform("cubeMap", "samplerCube"));
}

void SkyBoxShader::loadViewMatrix(glm::mat4 matrix) {
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    DefaultUnlitShader::loadViewMatrix(matrix);
}

void SkyBoxShader::bindAttributes() {
    bindAttribute(0, "position");
}