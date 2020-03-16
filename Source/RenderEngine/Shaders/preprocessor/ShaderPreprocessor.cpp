//
// Created by Idrol on 25-09-2017.
//

#include "ShaderPreprocessor.h"
#include "ShaderSource.h"
#include <ios>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../Crypto/MD5.h"
#include "../../../Util/string_util.h"
#include "../../../Util/vector_util.h"


ShaderSource* ShaderPreprocessor::loadShader(std::string path, Shader *shader) {
    std::list<std::string> lines;
    std::string name = getNameFromPath(path);
    std::string data;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::vector<std::string> strs;
    try {
        std::cout << "[ShaderManager] Opening shader file " << path << std::endl;
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        data = shaderStream.str();
        strs = string_util::stringSplit(data, "\n");
    } catch (std::ifstream::failure e) {
		std::cout << "[ShaderManager] Could not read shader file!" << std::endl;
        exit(-1);
    }
    return new ShaderSource(strs, shader, name, getMD5HashForString(data));
}

std::string ShaderPreprocessor::getMD5HashForString(std::string data) {
    return md5(data);
}

std::string ShaderPreprocessor::getNameFromPath(std::string path) {
    std::vector<std::string> pathArray;
    pathArray = string_util::stringSplit(path, "\\");
    std::string fileName;
    fileName = pathArray.back();
    std::vector<std::string> fileNameArr;
    fileNameArr = string_util::stringSplit(fileName, ".");
    return fileNameArr.front();
}

void ShaderPreprocessor::preprocessShader(ShaderSource *shaderSource) {
    std::vector<std::string> vertexSourceLines;
    std::vector<std::string> fragmentSourceLines;
    std::cout << "[ShaderManager] Splitting shader source." << std::endl;
    splitShaderSource(shaderSource, vertexSourceLines, fragmentSourceLines);
    std::cout << "[ShaderManager] Generating uniforms." << std::endl;
    generateUniforms(shaderSource, vertexSourceLines, fragmentSourceLines);
    std::cout << "[ShaderManager] Building shaders." << std::endl;
    shaderSource->vertexShaderSource = buildShader(vertexSourceLines);
    shaderSource->fragmentShaderSource = buildShader(fragmentSourceLines);
    std::cout << "[ShaderManager] Caching shaders." << std::endl;
    cacheShader(shaderSource->vertexShaderSource, shaderSource, "vs");
    cacheShader(shaderSource->fragmentShaderSource, shaderSource, "fs");
}

void ShaderPreprocessor::cacheShader(std::string shader, ShaderSource *shaderSource, std::string fileExtension) {
    // TODO implement
}

std::string ShaderPreprocessor::buildShader(std::vector<std::string> sourceLines) {
    std::string shader;
    for(auto const& line: sourceLines) {
        shader += line + "\n";
    }
    return shader;
}

void ShaderPreprocessor::generateUniforms(ShaderSource *shaderSource, std::vector<std::string> &vertexSourceLines,
                                          std::vector<std::string> &fragmentSourceLines) {
    std::vector<std::string> uniformList;
    uniformList.push_back("#version " + std::to_string(shaderVersion));
    std::cout << "Shader has " << std::to_string(shaderSource->shader->getUniforms().size()) << " uniforms registered." << std::endl;
    for(auto const& uniform: shaderSource->shader->getUniforms()) {
        std::string uniformLine;
        if(uniform->type == "struct") {
            uniformList.push_back("uniform " + uniform->type + " " + uniform->structName + "{");
            std::vector<std::string> uniformVars;
            uniformVars = uniform->uniformStruct->getVariables();
            uniformList.insert(uniformList.end(), uniformVars.begin(), uniformVars.end());
            uniformLine = "} " + uniform->name;
        } else {
            uniformLine = "uniform " + uniform->type + " " + uniform->name;
        }
        if(uniform->length != 1) uniformLine += "[" + std::to_string(uniform->length) + "]";
        uniformLine += ";";
        uniformList.push_back(uniformLine);
    }
    vertexSourceLines.insert(vertexSourceLines.begin(), uniformList.begin(), uniformList.end());
    fragmentSourceLines.insert(fragmentSourceLines.begin(), uniformList.begin(), uniformList.end());
}

void ShaderPreprocessor::splitShaderSource(ShaderSource *shaderSource, std::vector<std::string> &vertexSourceLines,
                                           std::vector<std::string> &fragmentSourceLines) {
    std::vector<std::string>::iterator it;
    it = shaderSource->lines.begin();
    while(it != shaderSource->lines.end()) {
        std::string line = *it;
        it++;
        if(line == "//VERTEX") readShader(shaderSource, vertexSourceLines, it);
        else if(line == "//FRAGMENT") readShader(shaderSource, fragmentSourceLines, it);
    }
}

void ShaderPreprocessor::readShader(ShaderSource *shaderSource, std::vector<std::string> &sourceLines, std::vector<std::string>::iterator lineIterator) {
    while(lineIterator != shaderSource->lines.end()) {
        std::string line = *lineIterator;
        lineIterator++;
        if(line == "//END") break;
        else sourceLines.push_back(line);
    }
}

GLuint ShaderPreprocessor::createShaderProgram(ShaderSource *shaderSource) {
    GLuint programID = glCreateProgram();
    glAttachShader(programID, compileShader(shaderSource->vertexShaderSource, GL_VERTEX_SHADER));
    glAttachShader(programID, compileShader(shaderSource->fragmentShaderSource, GL_FRAGMENT_SHADER));
    return programID;
}

GLuint ShaderPreprocessor::compileShader(std::string source, GLenum shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    const char *c_str = source.c_str();
    glShaderSource(shaderID, 1, &c_str, NULL);
    glCompileShader(shaderID);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0) {
        std::vector<char> shaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
        std::cout << &shaderErrorMessage[0] << std::endl;
        if(Result == GL_FALSE) {
            exit(-1);
        }
    }
    return shaderID;
}