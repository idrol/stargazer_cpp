#pragma once

#include "ResourceTask.h"
#include <string>

class Texture;

class LoadTextureTask: public ResourceTask {
public:
    LoadTextureTask(Texture *texture, std::string path) {
        this->texture = texture;
        this->path = path;
    };
    void loadResource() override;

private:
    Texture *texture = nullptr;
    std::string path;
};
