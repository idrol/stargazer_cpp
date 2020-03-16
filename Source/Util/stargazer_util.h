#pragma once

#include <string>
#include <GLM/glm.hpp>

class Camera;

class stargazer_util {
public:
    static void loadTexture(std::string name, std::string location);
    static void compileLights();
    static void setCursorVisibility(int visibility);
    static void reloadProjectionMatrix(glm::mat4 projectionMatrix);
    static glm::mat4 createOrthoGraphicProjectionMatrix(float left, float right, float top, float bottom, float near, float far);
    static glm::mat4 createPerspectiveProjectionMatrix(float fov, float near_plane, float far_plane);
    static void clear();
    static glm::mat4 createViewMatrix(Camera *camera);
    static glm::vec3 toEulerAngles(glm::vec4 quaternion);
    static glm::vec4 toQuaternion(glm::vec3 rotation);
    static glm::vec3 toRadians(glm::vec3 rotation);
    static glm::vec3 toDegrees(glm::vec3 rotation);
    static glm::vec3 getScalarColor(glm::vec3 color);
    static glm::vec3 calculateSurfaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
};
