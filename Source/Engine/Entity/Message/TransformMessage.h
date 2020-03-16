#pragma once
#include "Message.h"
#include <GLM/glm.hpp>

class TransformMessage: public Message {
public:
	TransformMessage(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
		id = "TransformMessage";
	};
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};