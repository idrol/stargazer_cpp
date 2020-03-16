#pragma once

#include "Shader.h"

class BRDFShader: public Shader {
public:
    BRDFShader(): Shader("Engine/shaders/generic/brdf.shader") {};

    void bindAttributes() override;
    void preInit() override;
};
