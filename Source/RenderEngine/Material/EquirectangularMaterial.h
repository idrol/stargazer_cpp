#pragma once

#include "Material.h"
#include <GLM/glm.hpp>
#include <string>

class Texture;

class EquirectangularMaterial: public Material {
public:
    EquirectangularMaterial();
    void apply() override;
    void bindTextures() override;
    void setEquirectangularTexture(Texture *texture);
    void setEquirectangularTexture(std::string name);

private:
    Texture *equirectangularTexture;
};
