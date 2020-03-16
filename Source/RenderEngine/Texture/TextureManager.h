#pragma once

#include <map>
#include <vector>
#include <string>

class Texture;

class TextureManager {
public:
    static void initialize();
    static void registerDefaults();
    static std::vector<Texture*> getTextures();
    static void registerTextureWithName(std::string name, Texture *texture);
    static void registerTextureWithPath(std::string path, Texture *texture);
    static void registerTextureWithPath(std::string path);
    static void registerTexture(Texture *texture);
    static void registerHDRTextureWithPath(std::string path);
    static void registerHDRTextureWithName(std::string name, std::string path);
    static Texture* getTextureWithPath(std::string path);
    static Texture* getTextureWithName(std::string name);

    static Texture *getIrradianceTexture();
    static void setIrradianceTexture(Texture *texture);
    static void setIrradianceTexture(std::string name);

    static Texture *getPrefilterMap();
    static void setPrefilterMap(Texture *texture);
    static void setPrefilterMap(std::string name);

    static Texture *getBRDFLUT();
    static void setBRDFLUT(Texture *texture);
    static void setBRDFLUT(std::string name);

private:
    // The two variables below holds mappings betweens names and paths to texture ids. This is not a requirment and textures can exist without mappings.
    static std::map<std::string, Texture*> textureNameMapping; // Maps texture names to texture ids
    static std::map<std::string, Texture*> texturePathMapping; // Maps texture paths to textures in the textures variable


    static std::vector<Texture*> textures; // Holds every registered texture in the render engine
    static Texture *irradianceTexture;
    static Texture *prefilterMap;
    static Texture *brdfLUT;
};