#include "Transform.h"
#include "GLM/gtx/transform.hpp"
#include <iostream>
#include "Model.h"

Transform::Transform(Model *model) {
    this->model = model;
}

glm::mat4 Transform::compileTransform() {
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, position);
    transformation = glm::rotate(transformation, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    transformation = glm::rotate(transformation, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transformation = glm::rotate(transformation, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    transformation = glm::scale(transformation, size);
    if(child != NULL) {
        glm::mat4 childMatrix = child->compileTransform();
        transformation = childMatrix * transformation;
    }
    return transformation;
}

glm::vec3 Transform::getPosition() {
    return position;
}

glm::vec3 Transform::getRotation() {
    return rotation;
}

glm::vec3 Transform::getScale() {
    return size;
}

Transform* Transform::getChild() {
    return child;
}

Model* Transform::getModel() {
    return model;
}

bool Transform::isParent(Transform *transform) {
    return transform == transform->getModel()->getTransform();
}

void Transform::translate(glm::vec3 position) {
    this->position = position;
}

void Transform::rotate(glm::vec3 rotation) {
    this->rotation = rotation;
}

void Transform::scale(glm::vec3 size) {
    this->size = size;
}

Transform* Transform::pushMatrix() {
    child = new Transform(model);
    return child;
}

void Transform::centerRotationOrigin() {
    if(!Transform::isParent(this)) return;
    pushMatrix();
}
