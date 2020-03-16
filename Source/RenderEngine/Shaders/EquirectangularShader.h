#pragma once

#include "Shader.h"

class EquirectangularShader: public Shader {
public:
    EquirectangularShader(): Shader("Engine/shaders/generic/equirectangular.shader") {};

    void registerAllUniforms() override;
    void bindAttributes() override;
    void preInit() override;
};
