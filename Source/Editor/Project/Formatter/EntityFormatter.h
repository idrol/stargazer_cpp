#pragma once

#include <json.hpp>

class Entity;
class EntityManager;
class ComponentFormatManager;

class EntityFormatter {
public:
    EntityFormatter();
    nlohmann::json serialize(Entity *entity);
    void deserialize(nlohmann::json entityData, EntityManager *entityManager);

private:
    ComponentFormatManager *componentFormatManager = nullptr;
};


