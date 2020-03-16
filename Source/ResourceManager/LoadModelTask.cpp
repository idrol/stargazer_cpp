#include "LoadModelTask.h"
#include "../RenderEngine/Model/Model.h"
#include "../RenderEngine/Model/ModelLoader.h"

void LoadModelTask::loadResource() {
    ModelLoader::loadModel(model, path, localPath);
}
