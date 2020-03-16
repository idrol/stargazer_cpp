#include "PhysicsComponentFormatter.h"
#include "../../../../Engine/Entity/Entity.h"
#include "../../../../Engine/Entity/Component/PhysicsComponent.h"
#include "../../../../Engine/Entity/Component/TransformComponent.h"
#include <btBulletCollisionCommon.h>

nlohmann::json PhysicsComponentFormatter::serialize(Component *component) {
    PhysicsComponent *physicsComponent = (PhysicsComponent*)component;
    btRigidBody *rigidBody = physicsComponent->getRigidBody();

    std::string type;
    nlohmann::json size;

    btCollisionShape *collisionShape = rigidBody->getCollisionShape();

    if(physicsComponent->getCollisionShapeType() == sphereShape) {
        type = "sphere";
        size = physicsComponent->getRadius();
    } else if(physicsComponent->getCollisionShapeType() == boxShape) {
        type = "box";
        glm::vec3 halfExtents = physicsComponent->getBoxHalfExtents();
        size = {halfExtents.x, halfExtents.y, halfExtents.z};
    }

    nlohmann::json componentJson = {
            {"type", physicsComponent->getType()},
            {"name", physicsComponent->getName()},
            {"collision_shape", {
                                        {"type", type},
                                        {"mass", physicsComponent->getMass()},
                                        {"size", size},
                                        {"static", physicsComponent->isStatic()}
                                }}
    };
    return componentJson;
}

void PhysicsComponentFormatter::deserialize(nlohmann::json componentData, Entity *entity) {
    PhysicsComponent *physicsComponent = new PhysicsComponent(entity);
    nlohmann::json collisionShape = componentData["collision_shape"];
    std::string type = collisionShape["type"];
    bool staticState = collisionShape["static"];
    if(type == "sphere") {
        physicsComponent->configureSphereCollisionShape(collisionShape["size"].get<float>());
        if(staticState) {
            physicsComponent->configureStatic(nullptr);
        } else {
            physicsComponent->configureDynamic(nullptr, collisionShape["mass"]);
        }
    } else if(type == "box") {
        physicsComponent->configureBoxCollisionShape(glm::vec3(collisionShape["size"][0].get<float>(), collisionShape["size"][1].get<float>(), collisionShape["size"][2].get<float>()));
        if(staticState) {
            physicsComponent->configureStatic(nullptr);
        } else {
            physicsComponent->configureDynamic(nullptr, collisionShape["mass"]);
        }
    }
}
