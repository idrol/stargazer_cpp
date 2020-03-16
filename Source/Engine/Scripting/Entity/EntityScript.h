#pragma once

#include "../Script.h"
#include <vector>

class Entity;
class EntityScriptInstance;

class EntityScript: public Script {
public:
    EntityScript(std::string scriptFile): Script("Entity", scriptFile) {}

    void reInitialize() override;

    EntityScriptInstance *createInstance(Entity *entity);

private:
    std::vector<EntityScriptInstance*> instances;

};
