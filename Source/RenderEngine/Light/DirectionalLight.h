#pragma once

#include "Light.h"

class DirectionalLight: public Light {
public:
    DirectionalLight(glm::vec3 position, glm::vec3 color): Light(position, color, 1) {};
};
