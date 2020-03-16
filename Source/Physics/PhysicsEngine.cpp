#include "PhysicsEngine.h"
#include "DebugRenderer.h"
#include <algorithm>

void PhysicsEngine::initialize() {

    debugRenderer = new DebugRenderer();

	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

    debugRenderer->initializeModels();
    debugRenderer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    dynamicsWorld->setDebugDrawer(debugRenderer);
}

void PhysicsEngine::setGravity(glm::vec3 gravity) {
    this->gravity = gravity;
    dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}

void PhysicsEngine::registerRigidBody(btRigidBody *rigidBody) {
    dynamicsWorld->addRigidBody(rigidBody);
    rigidBodies.push_back(rigidBody);
}

glm::vec3 PhysicsEngine::getGravity() {
    return gravity;
}

void PhysicsEngine::update(float delta) {
    dynamicsWorld->stepSimulation(delta, 1);
}

void PhysicsEngine::deRegisterRigidBody(btRigidBody *rigidBody) {
    dynamicsWorld->removeRigidBody(rigidBody);
    auto it = std::find(rigidBodies.begin(), rigidBodies.end(), rigidBody);
    if(it != rigidBodies.end()) {
        rigidBodies.erase(it);
    }
}

void PhysicsEngine::drawDebugWorld(float delta) {
    debugRenderer->clearDataBuffers();
    dynamicsWorld->debugDrawWorld();
    debugRenderer->finalizeRender();
}

DebugRenderer *PhysicsEngine::getDebugRenderer() {
    return debugRenderer;
}

void PhysicsEngine::activateAllBodies() {
    for(auto & rigidBody: rigidBodies) {
        rigidBody->activate(false);
    }
}
