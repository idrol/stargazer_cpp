#include "ComponentFormatManager.h"
#include "Component/ModelComponentFormatter.h"
#include "Component/TransformComponentFormatter.h"
#include "Component/PhysicsComponentFormatter.h"
#include "Component/CameraComponentFormatter.h"
#include "Component/SimpleKeyboardComponentFormatter.h"
#include "Component/PointLightComponentFormatter.h"
#include "../../../Engine/Entity/Component/Component.h"
#include <iostream>

ComponentFormatManager::ComponentFormatManager() {
    registerComponentFormatter("ModelComponent", new ModelComponentFormatter());
    registerComponentFormatter("TransformComponent", new TransformComponentFormatter());
    registerComponentFormatter("PhysicsComponent", new PhysicsComponentFormatter());
    registerComponentFormatter("CameraComponent", new CameraComponentFormatter());
    registerComponentFormatter("SimpleKeyboardComponent", new SimpleKeyboardComponentFormatter());
    registerComponentFormatter("PointLightComponent", new PointLightComponentFormatter());
}

void ComponentFormatManager::registerComponentFormatter(std::string type, ComponentFormatter *componentFormatter) {
    componentFormatters[type] = componentFormatter;
}

nlohmann::json ComponentFormatManager::serialize(Component *component) {
    auto it = componentFormatters.find(component->getType());
    if(it == componentFormatters.end()) {
        std::cout << "Component " << component->getType() << " has no formatter registered. Component will not be saved." << std::endl;
        return nlohmann::json();
    }
    return it->second->serialize(component);
}

void ComponentFormatManager::deserialize(nlohmann::json componentData, Entity *entity) {
    std::string type = componentData["type"];
    auto it = componentFormatters.find(type);
    if(it == componentFormatters.end()) {
        std::cout << "Component " << type << " has no registered formatter and will not be loaded." << std::endl;
        return;
    }
    return it->second->deserialize(componentData, entity);
}
