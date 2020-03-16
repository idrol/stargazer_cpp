#pragma once

#include "Command.h"
#include <GLM/glm.hpp>

class ReloadViewMatrix: public Command {
public:
    explicit ReloadViewMatrix(glm::mat4 matrix);
    void execute() override;

private:
    glm::mat4 matrix;
};
