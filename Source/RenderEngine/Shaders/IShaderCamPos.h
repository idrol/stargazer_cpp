#pragma once

#include <GLM/glm.hpp>
#include <iostream>

class IShaderCamPos {
public:
    virtual void saveCamPos(glm::vec3 camPos) {
        std::cout << "I'm an idiot" << std::endl;
    };
};
