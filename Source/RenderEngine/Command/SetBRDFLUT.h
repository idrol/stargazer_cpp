#pragma once

#include "Command.h"
#include <string>

class SetBRDFLUT: public Command {
public:
    SetBRDFLUT(std::string name);
    void execute() override;

private:
    std::string name;
};
