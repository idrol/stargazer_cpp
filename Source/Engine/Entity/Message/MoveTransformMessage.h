#pragma once
#include "Message.h"
#include <GLM/glm.hpp>

class Component;

class MoveTransformMessage: public Message {
public:
	MoveTransformMessage(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, Component *sender) {
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
		this->sender = sender;
		id = "MoveTransformMessage";
	};
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	Component *sender;
};