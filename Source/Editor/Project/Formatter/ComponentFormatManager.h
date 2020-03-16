#pragma once

#include <string>
#include <map>
#include <json.hpp>

class ComponentFormatter;
class Component;
class Entity;

class ComponentFormatManager {
public:
    ComponentFormatManager();
    void registerComponentFormatter(std::string type, ComponentFormatter *componentFormatter);
    nlohmann::json serialize(Component *component);
    void deserialize(nlohmann::json componentData, Entity *entity);
private:
    std::map<std::string, ComponentFormatter*> componentFormatters;
};


