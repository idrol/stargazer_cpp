//
// Created by Idrol on 12-10-2017.
//

#include "PrefilterShader.h"

void PrefilterShader::registerAllUniforms() {
    registerUniform(new Uniform("enviormentMap", "samplerCube"));
    registerUniform(new Uniform("roughness", "float"));
}

void PrefilterShader::bindAttributes() {
    bindAttribute(0, "position");
}
