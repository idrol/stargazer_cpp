#pragma once

#include "../Shaders/Shader.h"
#include "../Shaders/preprocessor/Uniform.h"
#include <string>

class SimpleShader: public Shader {
public:
    SimpleShader(): Shader("Engine/shaders/postProcessing/simple.shader") {};
    void registerAllUniforms() override {
        registerUniform(new Uniform("colorTexture", "sampler2D"));
    };

    void bindAttributes() override {
        bindAttribute(0, "position");
    };
};


