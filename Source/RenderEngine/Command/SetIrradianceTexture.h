#pragma once

#include "Command.h"
#include <string>

class SetIrradianceTexture: public Command {
public:
    SetIrradianceTexture(std::string name);
    void execute() override;

private:
    std::string name;
};
