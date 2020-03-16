#pragma once

#include <string>

class Entity;
class Message;

class Component {
public:
	Component(Entity *entity, std::string id, std::string type);
	virtual ~Component() {};
	std::string getID() {return id;};
	void setEntity(Entity *entity) {this->entityHandle = entity;};
	virtual void update(float delta) {};
	virtual void render() {};
	virtual void sendMessage(Message *message) {};
	virtual void select() {};
	virtual void deselect() {};
	virtual void renderEditorInspector() {};
	virtual void reload() {};
    std::string getType() {return type;};
    std::string getName() {return id;};
    virtual void saveState() {};
    virtual void loadState() {};
    virtual void clearSavedState() {};
    virtual void onPlay() {
        saveState();
    };
    virtual void onStop() {
        loadState();
    };
    virtual void onLoad() {};
    virtual void onUnload() {};

	bool editorInspectorImplemented = false;

protected:
	std::string id;
	Entity *entityHandle = nullptr;
    std::string type;
};