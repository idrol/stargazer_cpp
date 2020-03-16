#pragma once

#include "Command.h"
#include <string>

class SetPrefilterMap: public Command {
public:
    SetPrefilterMap(std::string name);
    void execute() override;

private:
    std::string name;
};
