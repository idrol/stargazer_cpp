#include "EntityFormatter.h"
#include "../../../Engine/Entity/Entity.h"
#include "../../../Engine/Entity/EntityManager.h"
#include "../../../Engine/Entity/Component/Component.h"
#include "ComponentFormatManager.h"

nlohmann::json EntityFormatter::serialize(Entity *entity) {
    nlohmann::json jsonComponents;
    for(auto & it: entity->getComponents()) {
        nlohmann::json componentJson = componentFormatManager->serialize(it.second);
        if(!componentJson.empty()) {
            //jsonComponents.push_back(componentJson);
            jsonComponents[it.second->getName().c_str()] = componentJson;
        }
    }
    nlohmann::json entityData = {
            {"name", entity->getName()},
            {"type", "Entity"},
            {"components", jsonComponents}
    };
    return entityData;
}

void EntityFormatter::deserialize(nlohmann::json entityData, EntityManager *entityManager) {
    std::string type = entityData["type"];
    if(!type.empty() && type == "Entity") { // Only standard entites supported att this time
        Entity *entity = entityManager->createEntity();
        entity->setName(entityData["name"]);
        for(auto & element: entityData["components"]) {
            componentFormatManager->deserialize(element, entity);
        }
        entity->reload();
    }
}

EntityFormatter::EntityFormatter() {
    componentFormatManager = new ComponentFormatManager();
}
