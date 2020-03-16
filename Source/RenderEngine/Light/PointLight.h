#pragma once

#include "Light.h"

class PointLight: public Light {
public:
    PointLight(glm::vec3 position, glm::vec3 color, int intensity): Light(position, color, intensity) {};
};
