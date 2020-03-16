#pragma once

#include "Material.h"
#include <GLM/glm.hpp>

class Texture;

class UnlitMaterial: public Material {
public:
    UnlitMaterial();
    void apply() override;
    void bindTextures() override;

    void setDiffuseColor(glm::vec3 color);

private:
    glm::vec3 diffuseColor;
    Texture *diffuseTexture;
    bool useTexture;
};
