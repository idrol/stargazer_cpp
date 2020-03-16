#pragma once

#include "Shader.h"

class PrefilterShader: public Shader {
public:
    PrefilterShader(): Shader("Engine/shaders/generic/prefilter.shader") {};

    void registerAllUniforms() override;
    void bindAttributes() override;
};
