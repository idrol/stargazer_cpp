#pragma once

#include "Command.h"
#include <string>

class Model;
class TexturePromise;

class ConvertHDRToCubeMap: public Command {
public:
    ConvertHDRToCubeMap(std::string cubeMapName, std::string hdrName, Model *cubeModel, std::string path);
    void execute() override;
    TexturePromise *getTexturePromise();

private:
    std::string cubeMapName, hdrName, path;
    Model *cubeModel;
    TexturePromise *texturePromise = nullptr;
};
