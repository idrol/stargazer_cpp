#pragma once

#include <vector>
#include <map>
#include <string>
#include <GLM/glm.hpp>
#include <iostream>
class Component;
class EntityManager;
class Message;
class TransformComponent;
class EntityScriptInstance;

class Entity {
public:
	Entity(unsigned int handle, EntityManager *emHandle);
	~Entity();
	void render();
	void update(float delta);
	std::map<std::string, Component*> getComponents() {return components;};
	Component *getComponent(std::string id);
	template<class T> std::vector<T> getComponentsByType();
	void addComponent(Component *component);
	bool componentExists(std::string id);
	void removeComponent(std::string id);
	EntityManager *getEMHandle();
	TransformComponent *getTransform();
	void sendMessage(Message *message);
	void sendMessageToOthers(Message *message, Component *componet);
	std::string getName();
	void setName(std::string name, bool updateScript=true);
	void select();
	void deselect();
	void reload();
	void saveState();
	void loadState();
	void clearSavedState();
	virtual void onPlay();
	virtual void onStop();
	virtual void onLoad();
	virtual void onUnload();

private:

	EntityScriptInstance *scriptInstance;
	std::map<std::string, Component*> components;
	std::string name;
	unsigned int handle;
	EntityManager *emHandle = nullptr;
	bool savedState = false;
};