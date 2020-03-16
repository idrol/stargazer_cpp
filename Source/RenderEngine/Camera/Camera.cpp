#include "Camera.h"
#include "../RenderEngine.h"
#include "../Command/ReloadProjectionMatrix.h"
#include "../../Util/stargazer_util.h"

Camera::Camera(float fov, float near, float far) {
	RenderEngine::getInstance().addCommand(new ReloadProjectionMatrix(stargazer_util::createPerspectiveProjectionMatrix(fov, near, far)));
	this->fov = fov;
	this->near = near;
	this->far = far;
}

float Camera::getSensitivity() {
    return sensitivity;
}

void Camera::reload() {
	RenderEngine::getInstance().addCommand(new ReloadProjectionMatrix(stargazer_util::createPerspectiveProjectionMatrix(fov, near, far)));
}

double Camera::getMouseX() {
    return mouseX;
}

double Camera::getMouseY() {
    return mouseY;
}

void Camera::setPitch(float pitch) {
    this->pitch = pitch;
}

void Camera::setYaw(float yaw) {
    this->yaw = yaw;
}

void Camera::setRoll(float roll) {
    this->roll = roll;
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

void Camera::update() {

}

glm::vec3 Camera::getPosition() {
    return position;
}

float Camera::getPitch() {
    return pitch;
}

float Camera::getYaw() {
    return yaw;
}

float Camera::getRoll() {
    return roll;
}
