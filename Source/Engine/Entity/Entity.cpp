#include "Entity.h"
#include "EntityManager.h"
#include "Component/Component.h"
#include "Message/Message.h"
#include "Component\TransformComponent.h"
#include "../Scripting/Entity/EntityScript.h"
#include "../Scripting/Entity/EntityScriptInstance.h"
#include "../Scripting/ScriptingEngine.h"

Entity::Entity(unsigned int handle, EntityManager *emHandle) {
	this->handle = handle;
	this->emHandle = emHandle;
	name = "Entity";
	EntityScript *script = (EntityScript*)ScriptingEngine::getInstance().getScript("Entity");
	scriptInstance = script->createInstance(this);
}

Entity::~Entity() {
	for(auto & it: components) {
		delete it.second;
	}
}

std::string Entity::getName() {
	return name;
}

void Entity::setName(std::string name, bool updateScript) {
	this->name = name;
	if(updateScript)scriptInstance->setName(name);
}

void Entity::render() {
	for(auto & it: components) {
		it.second->render();
	}
}

void Entity::update(float delta) {
	scriptInstance->onUpdate(delta);
	for(auto & it: components) {
		it.second->update(delta);
	}
}

Component *Entity::getComponent(std::string id) {
	std::map<std::string, Component*>::iterator it;
	it = components.find(id);
	if(it != components.end()) return it->second;
	return nullptr;
}

template <class T>
std::vector<T> Entity::getComponentsByType() {
	std::vector<T> tComponents;
	for(auto & it: components) {
		if(dynamic_cast<T*>(it.second) != nullptr) {
			tComponents.push_back((T*)it.second);
		}
	}
	return tComponents;
}

void Entity::addComponent(Component *component) {
	components[component->getID()] = component; 
	component->setEntity(this);
}

bool Entity::componentExists(std::string id) {
	return components.find(id) != components.end();
}

void Entity::removeComponent(std::string id){
	std::map<std::string, Component*>::iterator it;
	it = components.find(id);
	if(it != components.end()) {
		components.erase(it);
		delete it->second;
	}
}

void Entity::sendMessage(Message *message) {
	for(auto & it: components) {
		it.second->sendMessage(message);
	}
}

void Entity::sendMessageToOthers(Message *message, Component *component) {
	for(auto & it: components) {
		if(it.second != component) {
			it.second->sendMessage(message);
		}
	}
}

TransformComponent *Entity::getTransform() {
	Component *component = getComponent("TransformComponent");
    if(component == nullptr) {
        // Create new transform component incase none exists
        TransformComponent *transform = new TransformComponent(this);
        return transform;
    } else  {
		if(TransformComponent *transform = dynamic_cast<TransformComponent*>(component)) {
			return transform;
		}
	}
	return nullptr;
}

EntityManager *Entity::getEMHandle()  {
	return emHandle;
}

void Entity::select() {
	for(auto & it: components) {
		it.second->select();
	}
}

void Entity::deselect() {
	for(auto & it: components) {
		it.second->deselect();
	}
}

void Entity::reload() {
	for(auto & it: components) {
		it.second->reload();
	}
}

void Entity::saveState() {
	for(auto & it: components) {
		it.second->saveState();
	}
	savedState = true;
}

void Entity::loadState() {
	if(!savedState) return;
	for(auto & it: components) {
		it.second->loadState();
	}
	clearSavedState();
}

void Entity::clearSavedState() {
	if(!savedState) return;
	for(auto & it: components) {
		it.second->clearSavedState();
	}
	savedState = false;
}

void Entity::onPlay() {
	scriptInstance->onStart();
    for(auto & it: components) {
        it.second->onPlay();
    }
}

void Entity::onStop() {
	scriptInstance->onStop();
    for(auto & it: components) {
        it.second->onStop();
    }
}

void Entity::onLoad() {
	scriptInstance->onLoad();
    for(auto & it: components) {
        it.second->onLoad();
    }
}

void Entity::onUnload() {
	scriptInstance->onUnload();
    for(auto & it: components) {
        it.second->onUnload();
    }
}
