#include "EditorCamera.h"
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Input/InputHandler.h"
#include "../RenderEngine/Camera/Camera.h"

void EditorCamera::update(float delta) {
    if(InputHandler::mouseState != GLFW_CURSOR_NORMAL) {
        glm::vec2 mouseDelta = InputHandler::getMouseDelta();
        glm::vec3 velocity;

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

        camera->setPosition(velocity + camera->getPosition());
        camera->setYaw(camera->getYaw() + (mouseDelta.x * camera->getSensitivity()));
        camera->setPitch(camera->getPitch() + (mouseDelta.y * camera->getSensitivity()));

        if(camera->getPitch() < -90.0f) camera->setPitch(-90.0f);
        if(camera->getPitch() > 90.0f) camera->setPitch(90.0f);

        camera->update();
    }
}

Camera *EditorCamera::getCamera() {
    return camera;
}
