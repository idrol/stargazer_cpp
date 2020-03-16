//
// Created by Idrol on 25-09-2017.
//

#include "ShaderSource.h"

ShaderSource::ShaderSource(std::vector<std::string> lines, Shader *shader, std::string shaderName, std::string fileHash) {
    this->lines = lines;
    this->shader = shader;
    this->shaderName = shaderName;
    this->fileHash = fileHash;
}
