#pragma once
#include "GLM/glm.hpp"

class Model;

class Transform {
public:
    explicit Transform(Model *model);
    glm::mat4 compileTransform();
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();
    Transform* getChild();
    Model* getModel();
    void centerRotationOrigin();
    static bool isParent(Transform *transform);
    void translate(glm::vec3 position);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 size);
    Transform* pushMatrix();
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f);
    Transform *child = NULL;
    Model *model;
};