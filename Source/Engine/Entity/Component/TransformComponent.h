#pragma once
#include "Component.h"
#include <GLM/glm.hpp>

class Message;

class TransformComponent: public Component {
public:
	TransformComponent(Entity *entity): Component(entity, "TransformComponent", "TransformComponent") {
	    editorInspectorImplemented = true;
	};
	glm::vec3 getPosition() {
		return position;
	};
	glm::vec3 getScale() {
		return scale;
	};
	glm::vec3 getRotation() {
		return rotation;
	};
	void setPosition(glm::vec3 position);
	void setScale(glm::vec3 scale);
	void setRotation(glm::vec3 rotation);
	void sendMessage(Message *message) override;
	void update(float delta) override;
	void reload() override;
	void saveState() override;
	void loadState() override;
	void renderEditorInspector() override;

private:
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec3 scale = glm::vec3(1,1,1);
	glm::vec3 rotation = glm::vec3(0,0,0);
	glm::vec3 savedPosition, savedScale, savedRotation;
};