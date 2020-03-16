#pragma once

#include <string>

class Shader;

class Material {
public:
    explicit Material(std::string type, Shader *shader);
    virtual void apply();
    virtual void bindTextures() {};
    Shader* getShader() {return shader;};
    std::string getType() {
        return type;
    };

protected:
    Shader *shader;
    virtual void setShaderProperties() {};
    std::string type;
};
