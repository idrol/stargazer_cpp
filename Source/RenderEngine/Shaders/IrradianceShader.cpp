//
// Created by Idrol on 12-10-2017.
//

#include "IrradianceShader.h"

void IrradianceShader::registerAllUniforms() {
    registerUniform(new Uniform("enviormentMap", "samplerCube"));
}

void IrradianceShader::bindAttributes() {
    bindAttribute(0, "position");
}

void IrradianceShader::preInit() {
    enableTransformationMatrix = false;
}
