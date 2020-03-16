#pragma once

#include "Component.h"
#include "../../../Physics/PhysicsEngine.h"

enum CollisionShapeType {
    sphereShape, boxShape
};

class PhysicsComponent: public Component{
public:
    PhysicsComponent(Entity *entity): Component(entity, "PhysicsComponent", "PhysicsComponent") {
        editorInspectorImplemented = true;
    };
    void configureSphereCollisionShape(float radius);
    void configureBoxCollisionShape(glm::vec3 boxHalfExtents);
    void configureStatic(TransformComponent *component);
    void configureDynamic(TransformComponent *component, float kg);
    void update(float delta);
    void sendMessage(Message *message) override;
    bool isStatic();
    void setStatic(bool staticSate);
    btRigidBody *getRigidBody() {
        return rigidBody;
    };
    float getMass() {
        return kg;
    };
    void setMass(float mass);
    void renderEditorInspector() override;
    CollisionShapeType getCollisionShapeType() {
        return collisionShapeType;
    }
    float getRadius() {
        return radius;
    }
    glm::vec3 getBoxHalfExtents() {
        return boxHalfExtents;
    }

private:
    btRigidBody *rigidBody = nullptr;
    btCollisionShape *collisionShape = nullptr;
    float kg = 0;
    float radius = 0;
    glm::vec3 boxHalfExtents;
    CollisionShapeType collisionShapeType;
    bool staticState = false;
};