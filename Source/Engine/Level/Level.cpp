#include "Level.h"
#include "../Entity/Entity.h"
#include "../Entity/EntityManager.h"
#include "../../RenderEngine/RenderEngine.h"
#include "../../RenderEngine/Scene.h"
#include "../../Util/skybox_util.h"
#include "../Entity/Component/ModelComponent.h"
#include "../../RenderEngine/Camera/Camera.h"
#include <iostream>
#include <fstream>
#include <json.hpp>
#include "../../Editor/Project/Formatter/LevelFormatter.h"
#include "../../Physics/PhysicsEngine.h"
#include "../../Engine/Scripting/ScriptingEngine.h"
#include "../Scripting/Level/LevelScriptInstance.h"

Level::Level(std::string levelName, std::string levelFile) {
	entityManager = new EntityManager(this);
	scene = new Scene();
    this->levelFile = levelFile;
    this->levelName = levelName;
}

Entity *Level::createEntity() {
	return entityManager->createEntity();
}

Entity *Level::getEntity(unsigned int id) {
	return entityManager->getEntity(id);
}

void Level::active() {
	RenderEngine::getInstance().setActiveScene(scene);
}

void Level::start() {
    play = true;
    PhysicsEngine::getInstance().activateAllBodies();
    if(mainCamera == nullptr) {
        std::cout << "Cannot play level no camera" << std::endl;
        unload();
        exit(-1);
    }
	scene->setCamera(mainCamera);
    scriptInstance->onStart();
	for(auto & it: entityManager->getEntites()) {
		it.second->onPlay();
	}
}

void Level::load() {
    PhysicsEngine::getInstance().initialize();
    std::ifstream levelFile;
    levelFile.open(this->levelFile);
    std::string levelData((std::istreambuf_iterator<char>(levelFile)),
                          (std::istreambuf_iterator<char>()));
    levelFile.close();
    nlohmann::json levelJson = nlohmann::json::parse(levelData);
    LevelFormatter::deserialize(levelJson, this);
    ScriptingEngine::getInstance().initialize();
    for(auto & it: entityManager->getEntites()) {
    	it.second->onLoad();
    }
}

void Level::update(float delta) {
    if(play) {
        PhysicsEngine::getInstance().update(delta);
        scriptInstance->onUpdate(delta);
        entityManager->update(delta);
    }
}

void Level::setSkybox(std::string name, std::string hdrFile, float size) {
	RenderEngine::getInstance().createPBRCubeMapFromHDR(name, hdrFile);
	RenderEngine::getInstance().cycleCommandBuffer();
	
	Entity *skyboxEntity = entityManager->createEntity();
	skyboxEntity->setName("Sky Box");
	ModelComponent *modelComponent = new ModelComponent(skyboxEntity, "ModelComponent");
	Model *skyboxModel = skybox_util::createSkyboxModel(name + "_cubemap", size);
	modelComponent->setModel(skyboxModel);
}

void Level::setMainCamera(Camera *camera) {
	mainCamera = camera;
}

void Level::screenResized() {
	if(scene->getCamera() != nullptr) {
		scene->getCamera()->reload();
	}
}

void Level::unload() {
    scriptInstance->onUnload();
	for(auto & it: entityManager->getEntites()) {
		it.second->onUnload();
	}
    std::ofstream levelFile;
    levelFile.open(this->levelFile);
    levelFile << LevelFormatter::serialize(this).dump(4);
    levelFile.close();
}

void Level::stop() {
    play = false;
    scriptInstance->onStop();
	for(auto & it: entityManager->getEntites()) {
		it.second->onStop();
	}
	for(auto & it: entityManager->getEntites()) {
		it.second->reload();
	}
}

void Level::setScriptInstance(LevelScriptInstance *scriptInstance) {
	this->scriptInstance = scriptInstance;
}
