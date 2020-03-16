#pragma once

#include <GLM/glm.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <vector>

class DebugRenderer;

class PhysicsEngine {
public:
    static PhysicsEngine &getInstance() {
        static PhysicsEngine instance;
        return instance;
    }
    PhysicsEngine(PhysicsEngine const&) = delete;
    void operator=(PhysicsEngine const&) = delete;

    void initialize();
    void setGravity(glm::vec3 gravity);
    void registerRigidBody(btRigidBody *rigidBody);
    void deRegisterRigidBody(btRigidBody *rigidBody);
    glm::vec3 getGravity();
    void update(float delta);
    void drawDebugWorld(float delta);
    void activateAllBodies();
    DebugRenderer *getDebugRenderer();

private:
    PhysicsEngine() {};
    btBroadphaseInterface *broadphase = nullptr;
    btDefaultCollisionConfiguration *collisionConfiguration = nullptr;
    btCollisionDispatcher *dispatcher = nullptr;
    btSequentialImpulseConstraintSolver *solver = nullptr;
    btDiscreteDynamicsWorld *dynamicsWorld = nullptr;
    glm::vec3 gravity = glm::vec3(0, -10, 0);
    DebugRenderer *debugRenderer = nullptr;
    std::vector<btRigidBody*> rigidBodies;
};
