#pragma once

#include <string>
#include "Command.h"

class LoadTexture: public Command {
public:
    LoadTexture(std::string loc);
    void execute() override;

private:
    std::string loc;
};
