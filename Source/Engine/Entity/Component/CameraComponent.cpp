#include "CameraComponent.h"
#include "../Message/Message.h"
#include "../Message/TransformMessage.h"
#include "../../../RenderEngine/Camera/Camera.h"
#include "../EntityManager.h"
#include "../Entity.h"
#include "../../Level/Level.h"
#include <iostream>

void CameraComponent::update(float delta) {
	TransformComponent *transformComponent = entityHandle->getTransform();
	camera->setPosition(transformComponent->getPosition());
	glm::vec3 rotation = transformComponent->getRotation();
	camera->setYaw(rotation.y);
	camera->setPitch(rotation.x);

	if(camera->getPitch() < -90.0f) camera->setPitch(-90.0f);
	if(camera->getPitch() > 90.0f) camera->setPitch(90.0f);

	camera->update();
}

CameraComponent::CameraComponent(Entity *entity, float fov, float near, float far): Component(entity, "CameraComponent", "CameraComponent") {
	this->camera = new Camera(fov, near, far);
	entity->getEMHandle()->getLevel()->setMainCamera(camera);
}