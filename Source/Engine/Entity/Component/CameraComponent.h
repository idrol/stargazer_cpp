#pragma once
#include "Component.h"
#include "TransformComponent.h"

class Message;
class Camera;

class CameraComponent: public Component {
public:
	CameraComponent(Entity *entity, Camera *camera): Component(entity, "CameraComponent", "CameraComponent") {
		this->camera = camera;
	};
	CameraComponent(Entity *entity, float fov, float near, float far);
	void update(float delta) override;
	Camera *getCamera() { return camera; };

private:
	Camera *camera;
	TransformComponent *transformComponent = nullptr;
};