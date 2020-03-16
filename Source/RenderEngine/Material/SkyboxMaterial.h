#pragma once

#include "Material.h"
#include <string>

class Texture;
class TexturePromise;

class SkyboxMaterial: public Material {
public:
    SkyboxMaterial();

    void bindTextures() override;
    Texture* getSkyBoxTexture();
    void setSkyBoxTexture(Texture *skyBoxTexture);
    void setSkyBoxTextureWithName(std::string name);
    void setSkyBoxTextureWithPath(std::string path);
    void setSkyBoxTexture(TexturePromise *texturePromise);
    bool hasSkyBoxTexture();
    void clearSkyBoxTexture();

private:
    Texture *skyBoxTexture = nullptr;
    TexturePromise *texturePromise = nullptr;
};
