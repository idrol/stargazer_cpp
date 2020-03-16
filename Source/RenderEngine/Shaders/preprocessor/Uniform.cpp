//
// Created by Idrol on 25-09-2017.
//

#include "Uniform.h"

Uniform::Uniform(std::string name, std::string type) {
    this->name = name;
    this->type = type;
}

Uniform::Uniform(std::string name, std::string structName, UniformStruct *uniformStruct): Uniform(name, "struct") {
    this->uniformStruct = uniformStruct;
    this->structName = structName;
}

Uniform::Uniform(std::string name, std::string type, int length): Uniform(name, type) {
    this->length = length;
}

Uniform::Uniform(std::string name, std::string structName, UniformStruct *uniformStruct, int length):
        Uniform(name, structName, uniformStruct) {
    this->length = length;
}

bool Uniform::operator==(const Uniform &other) const {
    return name == other.name;
}
