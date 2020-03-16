#include "SimpleKeyboardComponentFormatter.h"
#include "../../../../Engine/Entity/Component/SimpleKeyboardComponent.h"

nlohmann::json SimpleKeyboardComponentFormatter::serialize(Component *component) {
    SimpleKeyboardComponent *simpleKeyboardComponent = (SimpleKeyboardComponent*)component;
    nlohmann::json componentData = {
            {"type", simpleKeyboardComponent->getType()},
            {"name", simpleKeyboardComponent->getName()},
            {"speed", simpleKeyboardComponent->getSpeed()}
    };
    return componentData;
}

void SimpleKeyboardComponentFormatter::deserialize(nlohmann::json componentData, Entity *entity) {
    SimpleKeyboardComponent *simpleKeyboardComponent = new SimpleKeyboardComponent(entity);
    simpleKeyboardComponent->setSpeed(componentData["speed"]);
}
