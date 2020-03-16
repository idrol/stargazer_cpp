#include "GL/glew.h"
#include "Scene.h"
#include "Model/Model.h"
#include <iostream>
#include <GLM/ext.hpp>
#include <algorithm>

void Scene::disable3D() {
    enable3D = false;
}

void Scene::disable2D() {
    enable2D = false;
}

void Scene::register3DModel(Model *model) {
    models3D.push_back(model);
}

void Scene::register2DModel(Model *model) {
    models2D.push_back(model);
}

void Scene::remove3DModel(Model *model) {
	std::vector<Model*>::iterator it;
	it = std::find(models3D.begin(), models3D.end(), model);
	if(it != models3D.end()) {
		models3D.erase(it);
	}
}

void Scene::remove2DModel(Model *model) {
	std::vector<Model*>::iterator it;
	it = std::find(models2D.begin(), models2D.end(), model);
	if(it != models2D.end()) {
		models2D.erase(it);
	}
}

void Scene::setCamera(Camera *camera) {
    this->camera = camera;
}

Camera *Scene::getCamera() {
    return camera;
}

void Scene::render() {
    if(enable3D) renderPass3D();
    if(enable2D) renderPass2D();
}

bool Scene::isEnabled3D() {
    return enable3D;
}

bool Scene::isEnabled2D() {
    return enable2D;
}

void Scene::prepare3D() {
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void Scene::renderPass3D() {
    //std::cout << "[RenderEngine] " << "Preparing 3D scene" << std::endl;
    prepare3D();
    //std::cout << "[RenderEngine] " << "Rendering 3D models" << std::endl;
    renderModels(models3D);
}

void Scene::prepare2D() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
}

void Scene::renderPass2D() {
    prepare2D();
    renderModels(models2D);
}

void Scene::renderModels(vector<Model*> models) {
    for(auto & model: models) {
        model->draw();
    }
}

bool Scene::contains3DModel(Model *model) {
    for(auto & model3D: models3D) {
        if(model3D == model) return true;
    }
    return false;
}

bool Scene::contains2DModel(Model *model) {
    for(auto & model2D: models2D)  {
        if(model2D == model) return true;
    }
    return false;
}
