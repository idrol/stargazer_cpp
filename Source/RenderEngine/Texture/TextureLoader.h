#pragma once

#include <string>
#include <GL/glew.h>
#include <vector>


class Texture;
class Model;

class TextureLoader {
public:
    static Texture *getHDRTexture(std::string path);
    static Texture* getTexture(std::string path) {return getTexture(path, GL_TEXTURE_2D, GL_RGBA);};
    static Texture* getTexture(std::string path, GLenum target, GLenum dstPixel);
    static unsigned char *loadTextureData(std::string path, int &width, int &height, int &channels);
    static void loadDataToTexture(Texture *texture, unsigned char *data, int width, int height, int channels);
    static GLuint createTextureID();
    static int get2Fold(int fold);
    static Texture *convertHDRTextureToCubeMap(Texture *texture, Model *cubeModel);
    static Texture *generateIrradianceMapFromCubeMap(Texture *texture, Model *cubeModel);
    static Texture *prefilterCubeMap(Texture *texture, Model *cubeModel);
    static Texture *generateBRDFLut(Model *quadModel);

    static GLuint loadCubeMap(std::vector<std::string> texture_files);
};
