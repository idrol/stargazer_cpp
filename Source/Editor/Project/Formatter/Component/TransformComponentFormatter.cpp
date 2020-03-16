#include "TransformComponentFormatter.h"
#include "../../../../Engine/Entity/Component/Component.h"
#include "../../../../Engine/Entity/Component/TransformComponent.h"

nlohmann::json TransformComponentFormatter::serialize(Component *component) {
    TransformComponent *transformComponent = (TransformComponent*)component;
    nlohmann::json componentData = {
            {"name", transformComponent->getName()},
            {"type", transformComponent->getType()},
            {"pos", {transformComponent->getPosition().x, transformComponent->getPosition().y, transformComponent->getPosition().z}},
            {"rot", {transformComponent->getRotation().x, transformComponent->getRotation().y, transformComponent->getRotation().z}},
            {"scale", {transformComponent->getScale().x, transformComponent->getScale().y, transformComponent->getScale().z}}
    };
    return componentData;
}

void TransformComponentFormatter::deserialize(nlohmann::json componentData, Entity *entity) {
    TransformComponent *transformComponent = new TransformComponent(entity);
    transformComponent->setPosition(glm::vec3(componentData["pos"][0], componentData["pos"][1], componentData["pos"][2]));
    transformComponent->setRotation(glm::vec3(componentData["rot"][0], componentData["rot"][1], componentData["rot"][2]));
    transformComponent->setScale(glm::vec3(componentData["scale"][0], componentData["scale"][1], componentData["scale"][2]));
    ComponentFormatter::deserialize(componentData, entity);
}
