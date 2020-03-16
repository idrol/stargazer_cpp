//
// Created by Idrol on 25-09-2017.
//

#include "UniformStruct.h"

void UniformStruct::addVariable(std::string variableName, std::string variableType) {
    structVariableNames.push_back(variableName);
    structVariableTypes.push_back(variableType);
}

std::vector<std::string> UniformStruct::getVariables() {
    std::vector<std::string> variables;
    std::list<std::string>::const_iterator iterator1 = structVariableNames.begin();
    std::list<std::string>::const_iterator iterator2 = structVariableTypes.begin();
    while((iterator1 != structVariableNames.end()) && (iterator2 != structVariableTypes.end())) {
        variables.push_back(*iterator2 + " " + *iterator1 + ";");
        iterator1++;
        iterator2++;
    }
    return variables;
}