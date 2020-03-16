#pragma once

#include "Command.h"
#include <string>

class Model;
class TexturePromise;

class GenerateIrradianceMapFromCubeMap: public Command {
public:
    GenerateIrradianceMapFromCubeMap(std::string irradianceName, std::string cubeMapName, Model *cubeModel, std::string path);
    void execute() override;
    TexturePromise *getTexturePromise();

private:
    std::string irradianceName, cubeMapName, path;
    Model *cubeModel;
    TexturePromise *texturePromise = nullptr;
};