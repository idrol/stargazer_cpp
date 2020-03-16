#pragma once

#include "Shader.h"
#include <string>
#include <GLM/glm.hpp>

class DefaultUnlitShader: public Shader {
public:
    DefaultUnlitShader(): Shader("Engine/shaders/generic/defaultunlit.shader") {};
    explicit DefaultUnlitShader(std::string shader): Shader(shader) {};

    void registerAllUniforms() override;
    void bindAttributes() override;
    void loadUseTexture(bool useTexture);
    void loadDiffuseColor(glm::vec3 color);
};
