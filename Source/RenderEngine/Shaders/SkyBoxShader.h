#pragma once

#include "DefaultUnlitShader.h"

class SkyBoxShader: public DefaultUnlitShader {
public:
    SkyBoxShader(): DefaultUnlitShader("Engine/shaders/generic/skybox.shader") {};

    void registerAllUniforms() override;
    void loadViewMatrix(glm::mat4 matrix) override;
    void bindAttributes() override;

};
