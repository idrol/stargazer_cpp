//
// Created by Idrol on 21-04-2018.
//

#include "EntityScript.h"
#include "EntityScriptInstance.h"

void EntityScript::reInitialize() {
    Script::reInitialize();
    for(auto & instance: instances) {
        instance->reInitialize();
    }
}

EntityScriptInstance *EntityScript::createInstance(Entity *entity) {
    EntityScriptInstance *instance = new EntityScriptInstance(entity, this);
    instances.push_back(instance);
    return instance;
}
