#include "EntityManager.h"
#include "Entity.h"

EntityManager::~EntityManager() {
	for(auto & it: entites) {
		delete it.second;
	}
}

Entity *EntityManager::createEntity() {
	Entity *entity = new Entity(++counter, this);
	entites[counter] = entity;
	return entity;
}

Entity *EntityManager::getEntity(unsigned int id) {
	std::map<unsigned int, Entity*>::iterator it;
	it = entites.find(id);
	if(it != entites.end()) {
		return it->second;
	}
	return nullptr;
}

void EntityManager::removeEntity(unsigned int id) {
	std::map<unsigned int, Entity*>::iterator it;
	it = entites.find(id);
	if(it != entites.end()) {
		delete it->second;
	}
	entites.erase(it);
}

void EntityManager::update(float delta) {
	for(auto & it: entites) {
		it.second->update(delta);
	}
}

void EntityManager::render() {
	for(auto & it: entites) {
		it.second->render();
	}
}

std::map<unsigned int, std::string> EntityManager::getEntityNameList() {
	std::map<unsigned int, std::string> entityNameList;
	for(auto & it: entites) {
		entityNameList[it.first] = it.second->getName();
	}
	return entityNameList;
}