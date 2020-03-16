#pragma once

#include "Command.h"
#include <string>

class Model;
class TexturePromise;

class PrefilterCubeMap: public Command {
public:
    PrefilterCubeMap(std::string prefilterName, std::string cubeMapName, Model *cubeModel, std::string path);
    void execute() override;
    TexturePromise *getTexturePromise();

private:
    std::string prefilterName, cubeMapName, path;
    Model *cubeModel;
    TexturePromise *texturePromise = nullptr;
};
