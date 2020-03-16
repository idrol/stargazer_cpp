#include "TransformComponent.h"
#include "../Entity.h"
#include "../Message/TransformMessage.h"
#include "../Message/MoveTransformMessage.h"
#include "../../../GUI/imgui.h"

void TransformComponent::setPosition(glm::vec3 position) {
	this->position = position;
	entityHandle->sendMessageToOthers(new TransformMessage(position, scale, rotation), this);
};
void TransformComponent::setScale(glm::vec3 scale) {
	this->scale = scale;
	entityHandle->sendMessageToOthers(new TransformMessage(position, scale, rotation), this);
};
void TransformComponent::setRotation(glm::vec3 rotation) {
	this->rotation = rotation;
	entityHandle->sendMessageToOthers(new TransformMessage(position, scale, rotation), this);
};

void TransformComponent::sendMessage(Message *message) {
	if(message->id == "MoveTransformMessage") {
        if(MoveTransformMessage *moveTransformMessage = dynamic_cast<MoveTransformMessage*>(message)) {
            this->position = moveTransformMessage->position;
            this->scale = moveTransformMessage->scale;
            this->rotation = moveTransformMessage->rotation;
            TransformMessage *transformMessage = new TransformMessage(position, scale, rotation);
            // Send position update to all other components but not the component that issued the message
            entityHandle->sendMessageToOthers(transformMessage, moveTransformMessage->sender);
        }
	}
}

void TransformComponent::update(float delta) {

}

void TransformComponent::reload() {
    entityHandle->sendMessageToOthers(new TransformMessage(position, scale, rotation), this);
}

void TransformComponent::saveState() {
	savedPosition = position;
	savedScale = scale;
	savedRotation = rotation;
}

void TransformComponent::loadState() {
	position = savedPosition;
	scale = savedScale;
	rotation = savedRotation;
	entityHandle->sendMessageToOthers(new TransformMessage(position, scale, rotation), this);
}

void TransformComponent::renderEditorInspector() {
	bool transformChanged = false;
	ImGui::Text("Transform");

	float pos3[3] = {position.x, position.y, position.z};
	ImGui::InputFloat3("Position", pos3);
	glm::vec3 updatedPosition(pos3[0], pos3[1], pos3[2]);
	if(position != updatedPosition) {
		position = updatedPosition;
		transformChanged = true;
	}
	float scale3[3] = {scale.x, scale.y, scale.z};
	ImGui::InputFloat3("Scale", scale3);
	glm::vec3 updatedScale(scale3[0], scale3[1], scale3[2]);
	if(scale != updatedScale) {
		scale = updatedScale;
		transformChanged = true;
	}

	float rot3[3] = {rotation.x, rotation.y, rotation.z};
	ImGui::InputFloat3("Rotation", rot3);
	glm::vec3 updatedRotation(rot3[0], rot3[1], rot3[2]);
	if(rotation != updatedRotation) {
		rotation = updatedRotation;
		transformChanged = true;
	}

	if(!transformChanged) return;
	entityHandle->sendMessageToOthers(new TransformMessage(position, scale, rotation), this);
}
