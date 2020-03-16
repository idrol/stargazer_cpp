#pragma once

#include "Command.h"
#include <GLM/glm.hpp>

class ReloadProjectionMatrix: public Command {
public:
    ReloadProjectionMatrix(glm::mat4 matrix);
    void execute() override;

private:
    glm::mat4 matrix;
};