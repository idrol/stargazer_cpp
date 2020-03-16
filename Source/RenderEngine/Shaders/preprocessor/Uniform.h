#pragma once

#include <string>
#include "UniformStruct.h"

class Uniform {
public:
    std::string name, type, structName;
    UniformStruct *uniformStruct;
    int length = 1;

    Uniform(std::string name, std::string type);
    Uniform(std::string name, std::string structName, UniformStruct *uniformStruct);
    Uniform(std::string name, std::string type, int length);
    Uniform(std::string name, std::string structName, UniformStruct *uniformStruct, int length);
    bool operator==(const Uniform& other) const;
};
