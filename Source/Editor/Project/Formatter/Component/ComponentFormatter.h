#pragma once

#include <json.hpp>

class Component;
class Entity;

class ComponentFormatter {
public:
    virtual nlohmann::json serialize(Component *component) { return nlohmann::json {};};
    virtual void deserialize(nlohmann::json componentData, Entity *entity) {};
};


