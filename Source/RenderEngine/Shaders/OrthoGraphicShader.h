#pragma once

#include "DefaultUnlitShader.h"

class OrthoGraphicShader: public DefaultUnlitShader {
public:
    explicit OrthoGraphicShader(std::string shader): DefaultUnlitShader(shader) {};
    OrthoGraphicShader(): OrthoGraphicShader("Engine/shaders/generic/orthoGraphic.shader") {};

    void bindAttributes() override;
};