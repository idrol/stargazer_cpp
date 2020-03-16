//
// Created by Idrol on 10-10-2017.
//

#include "EquirectangularShader.h"

void EquirectangularShader::registerAllUniforms() {
    registerUniform(new Uniform("equirectangularMap", "sampler2D"));
}

void EquirectangularShader::bindAttributes() {
    bindAttribute(0, "position");
}

void EquirectangularShader::preInit() {
    enableTransformationMatrix = false;
}
