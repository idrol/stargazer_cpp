#include "StargazerEngine.h"
#include "Level\Level.h"
#include "../Engine/Scripting/ScriptingEngine.h"

void StargazerEngine::switchLevel(Level *level) {
	if(this->level != nullptr) {
		this->level->unload();
		delete this->level;
	}
	level->load();
	this->level = level;
	this->level->active();
	this->level->screenResized();
}

void StargazerEngine::shutdownEngine() {
	if(this->level != nullptr) {
		this->level->unload();
		delete this->level;
	}
}

EntityManager *StargazerEngine::getEntityManager() {
	return this->level->getEntityManager();
}

void StargazerEngine::removeLevel(std::string name)  {
	std::map<std::string, Level*>::iterator it;
	it = levels.find(name);
	if(it != levels.end()) {
		levels.erase(it);
		Level *level = it->second;
		delete level;
	}
}

Level *StargazerEngine::getLevel(std::string name)  {
	std::map<std::string, Level*>::iterator it;
	it = levels.find(name);
	if(it != levels.end()) {
		return it->second;
	}
	return nullptr;
}

void StargazerEngine::startEngine() {
	ScriptingEngine::getInstance().createStargazerLibrary();
};