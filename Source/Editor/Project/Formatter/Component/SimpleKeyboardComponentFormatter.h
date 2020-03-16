#pragma once

#include "ComponentFormatter.h"

class SimpleKeyboardComponentFormatter: public ComponentFormatter {
public:
    nlohmann::json serialize(Component *component) override;
    void deserialize(nlohmann::json componentData, Entity *entity) override;
};


