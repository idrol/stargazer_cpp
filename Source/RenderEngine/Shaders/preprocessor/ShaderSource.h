#pragma once

#include <string>
#include <list>
#include <vector>
#include "../Shader.h"

class ShaderSource {
public:
    std::string shaderName, fileHash;
    std::vector<std::string> lines;
    Shader *shader;
    std::string vertexShaderSource, fragmentShaderSource;

    ShaderSource(std::vector<std::string> lines, Shader *shader, std::string shaderName, std::string fileHash);
};
