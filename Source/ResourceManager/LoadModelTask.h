#pragma once

#include "ResourceTask.h"
#include <string>

class Model;

class LoadModelTask: public ResourceTask {
public:
    LoadModelTask(Model *model, std::string path, std::string localPath) {
        this->model = model;
        this->path = path;
        this->localPath = localPath;
    };
    void loadResource() override;

private:
    Model *model = nullptr;
    std::string path, localPath;
};
