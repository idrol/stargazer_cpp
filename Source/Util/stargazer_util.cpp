//
// Created by Idrol on 02-10-2017.
//

#include "stargazer_util.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "../RenderEngine/Command/ReloadProjectionMatrix.h"
#include "../RenderEngine/Window/WindowUtil.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/Camera/Camera.h"
#include "../RenderEngine/Command/CompileLights.h"
#include <iostream>
#include <GLM/ext.hpp>

void stargazer_util::loadTexture(std::string name, std::string location) {
    // TODO
}

void stargazer_util::compileLights() {
    RenderEngine::getInstance().addCommand(new CompileLights());
}

void stargazer_util::setCursorVisibility(int visibility) {
    // TODO
}

void stargazer_util::reloadProjectionMatrix(glm::mat4 projectionMatrix) {
    RenderEngine::getInstance().addCommand(new ReloadProjectionMatrix(projectionMatrix));
}

glm::mat4 stargazer_util::createOrthoGraphicProjectionMatrix(float left, float right, float top, float bottom, float near_plane, float far_plane) {
    return glm::ortho(left, right, bottom, top, near_plane, far_plane);
}

glm::mat4 stargazer_util::createPerspectiveProjectionMatrix(float fov, float near_plane, float far_plane) {
	glm::vec2 vec = RenderEngine::getInstance().getRenderScale();
    float aspect_ration = (float)vec.x/(float)vec.y;
    return glm::perspective(glm::radians(fov), aspect_ration, near_plane, far_plane);
}

void stargazer_util::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::vec3 color = RenderEngine::getInstance().getClearColor();
    glClearColor(color.x, color.y, color.z, 1);
}

glm::mat4 stargazer_util::createViewMatrix(Camera *camera) {
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->getPitch()), glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->getYaw()), glm::vec3(0, 1, 0));
    viewMatrix = glm::translate(viewMatrix, -camera->getPosition());
    return viewMatrix;
}

glm::vec3 stargazer_util::getScalarColor(glm::vec3 color) {
    return glm::vec3(color.x/255, color.y/255, color.z/255);
}

glm::vec3 stargazer_util::calculateSurfaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
    // TODO
    return glm::vec3();
}

glm::vec3 stargazer_util::toEulerAngles(glm::vec4 q) {
    glm::vec3 rotation;

    float sinr = 2.0f * (q.w * q.x + q.y * q.z);
    float cosr = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    rotation.x = atan2f(sinr, cosr);

    float sinp = 2.0f * (q.w * q.y - q.z * q.x);
    if(fabsf(sinp) >= 1)
        rotation.y = copysignf((float)M_PI / 2, sinp);
    else
        rotation.y = asinf(sinp);

    float siny = 2.0f * (q.w * q.z + q.x * q.y);
    float cosy = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    rotation.z = atan2f(siny, cosy);

    return rotation;
}

glm::vec4 stargazer_util::toQuaternion(glm::vec3 rotation) {
    glm::vec4 quaternion;

    float cy = cosf(rotation.z * 0.5f);
    float sy = sinf(rotation.z * 0.5f);
    float cr = cosf(rotation.x * 0.5f);
    float sr = sinf(rotation.x * 0.5f);
    float cp = cosf(rotation.y * 0.5f);
    float sp = sinf(rotation.y * 0.5f);

    quaternion.w = cy * cr * cp + sy * sr * sp;
    quaternion.x = cy * sr * cp - sy * cr * sp;
    quaternion.y = cy * cr * sp + sy * sr * cp;
    quaternion.z = sy * cr * cp - cy * sr * sp;
    return quaternion;
}

glm::vec3 stargazer_util::toRadians(glm::vec3 rotation) {
    return glm::vec3(rotation.x * M_PI/180, rotation.y * M_PI/180, rotation.z * M_PI/180);
}

glm::vec3 stargazer_util::toDegrees(glm::vec3 rotation) {
    return glm::vec3(rotation.x * 180/M_PI, rotation.y*180/M_PI, rotation.z*180/M_PI);
}
