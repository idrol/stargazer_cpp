#pragma once

#include "Shader.h"

class IrradianceShader: public Shader {
public:
    IrradianceShader(): Shader("Engine/shaders/generic/irradiance.shader") {};

    void registerAllUniforms() override;
    void bindAttributes() override;
    void preInit() override;
};
