//
// Created by Idrol on 12-10-2017.
//

#include "BRDFShader.h"

void BRDFShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "inTexCoords");
}

void BRDFShader::preInit() {
    enableTransformationMatrix = false;
    enableViewMatrix = false;
    enableProjectionMatrix = false;
}
