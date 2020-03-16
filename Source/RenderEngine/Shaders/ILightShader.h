#pragma once

#include <vector>
#include "../Light/Light.h"

class ILightShader {
public:
    virtual void loadLights(std::vector<Light*> lights) {};
};
