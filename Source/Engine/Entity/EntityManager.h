#pragma once

#include <map>

class Entity;
class Level;

class EntityManager {
public:
	EntityManager(Level *level) {
		this->level = level;
	};
	~EntityManager();
	Entity *createEntity();
	Entity *getEntity(unsigned int id);
	void removeEntity(unsigned int id);
	void render();
	void update(float delta);
	Level *getLevel() {
		return level;
	};
	std::map<unsigned int, Entity*> getEntites() {
		return entites;
	};
	std::map<unsigned int, std::string> getEntityNameList();

private:
	std::map<unsigned int, Entity*> entites;
	unsigned int counter = 0;
	Level *level;
};