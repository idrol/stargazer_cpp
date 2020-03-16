//
// Created by Idrol on 17-11-2017.
//

#include <iostream>
#include <string>
#include "../Entity.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "../Message/Message.h"
#include "../Message/TransformMessage.h"
#include "../Message/MoveTransformMessage.h"
#include "../../../GUI/imgui.h"
#include "../../../Util/StargazerUtil.h"

void PhysicsComponent::configureStatic(TransformComponent *component) {
    staticState = true;
    kg = 0;
    btTransform initialTransform;
    glm::vec3 position, rotation, scale(1,1,1);
    if(component != nullptr) {
        position = component->getPosition();
        rotation = stargazer_util::toRadians(component->getRotation());
        scale = component->getScale();
    }

    initialTransform.setOrigin(btVector3(position.x, position.y, position.z));

    btQuaternion quaternion;
    quaternion.setEulerZYX(rotation.z, rotation.y, rotation.x);
    initialTransform.setRotation(quaternion);

    btDefaultMotionState *motionState = new btDefaultMotionState(initialTransform);

    collisionShape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, motionState, collisionShape, btVector3(0,0,0));
    rigidBody = new btRigidBody(rigidBodyCI);
    PhysicsEngine::getInstance().registerRigidBody(rigidBody);
}

void PhysicsComponent::configureDynamic(TransformComponent *component, float kg) {
    this->kg = kg;
    btTransform initialTransform;
    glm::vec3 position, rotation, scale(1,1,1);
    if(component != nullptr) {
        position = component->getPosition();
        rotation = stargazer_util::toRadians(component->getRotation());
        scale = component->getScale();
    }

    initialTransform.setOrigin(btVector3(position.x, position.y, position.z));

    btQuaternion quaternion;
    quaternion.setEulerZYX(rotation.z, rotation.y, rotation.x);
    initialTransform.setRotation(quaternion);

    btDefaultMotionState *motionState = new btDefaultMotionState(initialTransform);
    btScalar mass = kg;
    btVector3 fallInertia(0,0,0);
    collisionShape->calculateLocalInertia(mass, fallInertia);

    collisionShape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, collisionShape, fallInertia);
    rigidBody = new btRigidBody(rigidBodyCI);
    PhysicsEngine::getInstance().registerRigidBody(rigidBody);
}

void PhysicsComponent::update(float delta) {
    if(isStatic()) return;
    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);
    glm::vec3 position(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
    btVector3 localScale = rigidBody->getCollisionShape()->getLocalScaling();
    glm::vec3 scale(localScale.x(), localScale.y(), localScale.z());
    btScalar roll, pitch, yaw;
    trans.getRotation().getEulerZYX(yaw, pitch, roll);
    glm::vec3 rotation(roll, pitch, yaw); // Radians
    MoveTransformMessage *moveTransformMessage = new MoveTransformMessage(position, scale, stargazer_util::toDegrees(rotation), this);
    entityHandle->sendMessageToOthers(moveTransformMessage, this);
}

void PhysicsComponent::sendMessage(Message *message) {
    if(message->id == "TransformMessage") {
        if(TransformMessage *transformMessage = dynamic_cast<TransformMessage*>(message)) {
            PhysicsEngine::getInstance().deRegisterRigidBody(rigidBody);
            btTransform transform;
            transform.setOrigin(btVector3(transformMessage->position.x, transformMessage->position.y, transformMessage->position.z));
            glm::vec3 rotation = stargazer_util::toRadians(transformMessage->rotation);
            btQuaternion quaternion;
            quaternion.setEulerZYX(rotation.z, rotation.y, rotation.x);
            transform.setRotation(quaternion);
            rigidBody->setWorldTransform(transform);
            rigidBody->clearForces();
            rigidBody->setAngularVelocity(btVector3(0,0,0));
            rigidBody->setLinearVelocity(btVector3(0,0,0));
            glm::vec3 scale = transformMessage->scale;
            rigidBody->getCollisionShape()->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
            PhysicsEngine::getInstance().registerRigidBody(rigidBody);
        }
    }
}

bool PhysicsComponent::isStatic() {
    return staticState;
}

void PhysicsComponent::setStatic(bool staticSate) {
    if(this->staticState != staticSate) {
        this->staticState = staticSate;
        if(staticSate) {
            // Static
            PhysicsEngine::getInstance().deRegisterRigidBody(rigidBody);
            rigidBody->setMassProps(0, btVector3(0,0,0));
            PhysicsEngine::getInstance().registerRigidBody(rigidBody);
        } else {
            // Dynamic
            PhysicsEngine::getInstance().deRegisterRigidBody(rigidBody);
            rigidBody->setMassProps(kg, btVector3(0,0,0));
            PhysicsEngine::getInstance().registerRigidBody(rigidBody);
        }
    }
}

void PhysicsComponent::setMass(float mass) {
    kg = mass;
    if(!isStatic()) {
        PhysicsEngine::getInstance().deRegisterRigidBody(rigidBody);
        rigidBody->setMassProps(kg, btVector3(0,0,0));
        PhysicsEngine::getInstance().registerRigidBody(rigidBody);
    }
}

void PhysicsComponent::renderEditorInspector() {
    ImGui::Text("Physics Component");

    float mass = kg;
    ImGui::InputFloat("Mass", &mass);
    if(mass != kg) {
        setMass(mass);
    }
    bool staticState = this->staticState;
    ImGui::Checkbox("Static", &staticState);
    if(staticState != this->staticState) {
        setStatic(staticState);
    }
}

void PhysicsComponent::configureSphereCollisionShape(float radius) {
    this->radius = radius;
    collisionShape = new btSphereShape(radius);
    collisionShapeType = sphereShape;
}

void PhysicsComponent::configureBoxCollisionShape(glm::vec3 boxHalfExtents) {
    this->boxHalfExtents = boxHalfExtents;
    collisionShape = new btBoxShape(btVector3(boxHalfExtents.x, boxHalfExtents.y, boxHalfExtents.z));
    collisionShapeType = boxShape;
}
