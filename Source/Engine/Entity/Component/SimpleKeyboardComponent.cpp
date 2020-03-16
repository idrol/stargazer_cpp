#include "SimpleKeyboardComponent.h"
#include <GLM/glm.hpp>
#include "../../../Input/InputHandler.h"
#include "../../../RenderEngine/Camera/Camera.h"
#include "../Entity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include <GLFW/glfw3.h>
#include "../Message/TransformMessage.h"
#include "../Message/MoveTransformMessage.h"

void SimpleKeyboardComponent::update(float delta) {
	if(InputHandler::mouseState != GLFW_CURSOR_NORMAL) {
		glm::vec2 mouseDelta = InputHandler::getMouseDelta();
		glm::vec3 velocity;

		Component *component = entityHandle->getComponent("CameraComponent");
		if(component == nullptr || entityHandle->getTransform() == nullptr) return;
		CameraComponent *cameraComponent = dynamic_cast<CameraComponent*> (component);
		if(cameraComponent == nullptr) return;
		Camera *camera = cameraComponent->getCamera();

		if(InputHandler::getKeyState(GLFW_KEY_A) != GLFW_RELEASE) {
			velocity.z -= (float) (speed * sin(glm::radians(camera->getYaw()))) * delta;
			velocity.x -= (float) (speed * cos(glm::radians(camera->getYaw()))) * delta;
		}
		if(InputHandler::getKeyState(GLFW_KEY_D) != GLFW_RELEASE) {
			velocity.z += (float) (speed * sin(glm::radians(camera->getYaw()))) * delta;
			velocity.x += (float) (speed * cos(glm::radians(camera->getYaw()))) * delta;
		}
		if(InputHandler::getKeyState(GLFW_KEY_S) != GLFW_RELEASE) {
			velocity.z += (float) (speed * sin(glm::radians(camera->getYaw() + 90))) * delta;
			velocity.x += (float) (speed * cos(glm::radians(camera->getYaw() + 90))) * delta;
		}
		if(InputHandler::getKeyState(GLFW_KEY_W) != GLFW_RELEASE) {
			velocity.z -= (float) (speed * sin(glm::radians(camera->getYaw() + 90))) * delta;
			velocity.x -= (float) (speed * cos(glm::radians(camera->getYaw() + 90))) * delta;
		}
		if(InputHandler::getKeyState(GLFW_KEY_SPACE) != GLFW_RELEASE) {
			velocity.y += speed * delta;
		}
		if(InputHandler::getKeyState(GLFW_KEY_LEFT_SHIFT) != GLFW_RELEASE) {
			velocity.y -= speed * delta;
		}
		TransformComponent *transformComponent = entityHandle->getTransform();
		glm::vec3 position;
		glm::vec3 rotation;
		position = velocity + transformComponent->getPosition();
		rotation.x = camera->getPitch() + (mouseDelta.y * camera->getSensitivity());
		rotation.y = camera->getYaw() + (mouseDelta.x * camera->getSensitivity());
		MoveTransformMessage *moveTransformMessage = new MoveTransformMessage(position, glm::vec3(1,1,1), rotation, this);
		entityHandle->sendMessage(moveTransformMessage);
	}
}