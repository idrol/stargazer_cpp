#pragma once

#include "Material.h"
#include <string>

class Texture;

class PrefilterMaterial: public Material {
public:
    PrefilterMaterial();
    void apply() override;
    void bindTextures() override;
    void setEnviormentMap(Texture *texture);
    void setEnviormentMap(std::string name);
    void setRoughness(float roughness);

private:
    Texture *enviormentMap;
    float roughness = 0;
};
