#pragma once

#include "Command.h"
#include <string>

class TexturePromise;

class LoadHDRTexture: public Command {
public:
    LoadHDRTexture(std::string path);
    LoadHDRTexture(std::string name, std::string path);
    TexturePromise *getTexturePromise();
    void execute() override;

private:
    std::string path;
    std::string name = "";
    TexturePromise *texturePromise = nullptr;
};