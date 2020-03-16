//
// Created by Idrol on 29-09-2017.
//

#include "OrthoGraphicShader.h"

void OrthoGraphicShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "uv");
}
