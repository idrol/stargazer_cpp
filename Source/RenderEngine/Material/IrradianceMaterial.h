#pragma once

#include "Material.h"
#include <string>

class Texture;

class IrradianceMaterial: public Material {
public:
    IrradianceMaterial();
    void apply() override;
    void bindTextures() override;
    void setEnviormentMap(Texture *texture);
    void setEnviormentMap(std::string name);

private:
    Texture *enviormentMap;
};
