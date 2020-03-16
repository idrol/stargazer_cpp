#pragma once

#include <list>
#include <string>
#include <vector>

class UniformStruct {
public:
    void addVariable(std::string variableName, std::string variableType);
    std::vector<std::string> getVariables();
    std::list<std::string> getVariableNames() {return structVariableNames;};

private:
    std::list<std::string> structVariableNames;
    std::list<std::string> structVariableTypes;
};
