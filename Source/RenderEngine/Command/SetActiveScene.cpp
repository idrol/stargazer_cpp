//
// Created by Idrol on 02-10-2017.
//

#include "SetActiveScene.h"
#include "../RenderEngine.h"

SetActiveScene::SetActiveScene(Scene *scene) {
    this->scene = scene;
}

void SetActiveScene::execute() {
    RenderEngine::getInstance().setActiveScene(scene);
}
