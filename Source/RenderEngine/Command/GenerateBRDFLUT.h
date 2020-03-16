#pragma once

#include "Command.h"
#include <string>

class Model;

class GenerateBRDFLUT: public Command {
public:
    GenerateBRDFLUT(std::string name, Model *quadModel);
    void execute() override;

private:
    std::string name;
    Model *quadModel;
};
