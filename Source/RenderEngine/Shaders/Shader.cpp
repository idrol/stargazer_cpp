//
// Created by Idrol on 25-09-2017.
//

#include "Shader.h"
#include "preprocessor/ShaderPreprocessor.h"
#include "preprocessor/Uniform.h"
#include <iostream>
#include <string>
#include <GLM/ext.hpp>
#include "../../ResourceManager/ResourceManager.h"

Shader::Shader(std::string shaderFile) {
    this->shaderFile = ResourceManager::getInstance().resolvePath(shaderFile);
    if(enableTransformationMatrix) registerUniform(new Uniform("transformationMatrix", "mat4"));
    if(enableProjectionMatrix) registerUniform(new Uniform("projectionMatrix", "mat4"));
    if(enableViewMatrix) registerUniform(new Uniform("viewMatrix", "mat4"));
}

void Shader::init() {
    ShaderSource *shaderSource = ShaderPreprocessor::loadShader(shaderFile, this);
    registerAllUniforms();
    ShaderPreprocessor::preprocessShader(shaderSource);
    programID = ShaderPreprocessor::createShaderProgram(shaderSource);
    bindAttributes();
    glLinkProgram(programID);

    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetProgramiv(programID, GL_LINK_STATUS, &Result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::cout << &ProgramErrorMessage[0] << std::endl;
        if(Result == GL_FALSE){
            exit(-1);
        }
    }

    glValidateProgram(programID);
    preInit();
    loadUniformLocations();
    getAllUniformLocations();
    loadTextureAddresses();
}

bool Shader::isEnableProjectionMatrix() {
    return enableProjectionMatrix;
}

void Shader::setEnableProjectionMatrix(bool enableProjectionMatrix) {
    this->enableProjectionMatrix = enableProjectionMatrix;
}

bool Shader::isEnableViewMatrix() {
    return enableViewMatrix;
}

void Shader::setEnableViewMatrix(bool enableViewMatrix) {
    this->enableViewMatrix = enableViewMatrix;
}

bool Shader::isEnableTransformationMatrix() {
    return enableTransformationMatrix;
}

void Shader::setEnableTransformationMatrix(bool enableTransformationMatrix) {
    this->enableTransformationMatrix = enableTransformationMatrix;
}

void Shader::unregisterUniform(std::string uniform) {
    uniforms.remove(new Uniform(uniform, ""));
}

GLint Shader::getUniformLocation(std::string uniform) {
    return glGetUniformLocation(programID, uniform.c_str());
}

void Shader::start() {
    glUseProgram(programID);
}

void Shader::stop() {
    glUseProgram(0);
}

void Shader::loadInt(GLint location, GLint value) {
    glUniform1i(location, value);
}

void Shader::bindAttribute(GLuint location, std::string variable) {
    glBindAttribLocation(programID, location, variable.c_str());
}

void Shader::loadFloat(GLint location, GLfloat value) {
    glUniform1f(location, value);
}

void Shader::loadVector3f(GLint location, glm::vec3 value) {
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::loadVector4f(GLint location, glm::vec4 value) {
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::loadBool(GLint location, bool value) {
    if(value) {
        glUniform1f(location, 1);
    } else {
        glUniform1f(location, 0);
    }
}

void Shader::loadInt(std::string uniform, GLint value) {
    std::map<std::string, GLint>::iterator it;
    it = uniformLocations.find(uniform);
    if(it != uniformLocations.end()) {
        loadInt(it->second, value);
    } else {
        std::cout << "[RenderEngine] Could not load int because uniform " << uniform << " could not be found." << std::endl;
    }
}

void Shader::loadFloat(std::string uniform, GLfloat value) {
    std::map<std::string, GLint>::iterator it;
    it = uniformLocations.find(uniform);
    if(it != uniformLocations.end()) {
        loadFloat(it->second, value);
    } else {
        std::cout << "[RenderEngine] Could not load float because uniform " << uniform << " could not be found." << std::endl;
    }
}

void Shader::loadVector3f(std::string uniform, glm::vec3 value) {
    std::map<std::string, GLint>::iterator it;
    it = uniformLocations.find(uniform);
    if(it != uniformLocations.end()) {
        loadVector3f(it->second, value);
    } else {
        std::cout << "[RenderEngine] Could not load vec3 because uniform " << uniform << " could not be found." << std::endl;
    }
}

void Shader::loadVector4f(std::string uniform, glm::vec4 value) {
    std::map<std::string, GLint>::iterator it;
    it = uniformLocations.find(uniform);
    if(it != uniformLocations.end()) {
        loadVector4f(it->second, value);
    } else {
        std::cout << "[RenderEngine] Could not load vec4 because uniform " << uniform << " could not be found." << std::endl;
    }
}

void Shader::loadBool(std::string uniform, bool value) {
    std::map<std::string, GLint>::iterator it;
    it = uniformLocations.find(uniform);
    if(it != uniformLocations.end()) {
        loadBool(it->second, value);
    } else {
        std::cout << "[RenderEngine] Could not load bool because uniform " << uniform << " could not be found." << std::endl;
    }
}

void Shader::loadMatrix(GLint location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::loadTransformationMatrix(glm::mat4 matrix) {
    if(enableTransformationMatrix) {
        std::map<std::string, GLint>::iterator it;
        it = uniformLocations.find("transformationMatrix");
        if(it != uniformLocations.end()) {
            loadMatrix(it->second, matrix);
        }
    }
}

void Shader::loadProjectionMatrix(glm::mat4 matrix) {
    if(enableProjectionMatrix) {
        std::map<std::string, GLint>::iterator it;
        it = uniformLocations.find("projectionMatrix");
        if(it != uniformLocations.end()) {
            loadMatrix(it->second, matrix);
        }
    }
}

void Shader::loadViewMatrix(glm::mat4 matrix) {
    if(enableViewMatrix) {
        std::map<std::string, GLint>::iterator it;
        it = uniformLocations.find("viewMatrix");
        if(it != uniformLocations.end()) {
            loadMatrix(it->second, matrix);
        }
    }
}

GLint Shader::getStoredUniformLocation(std::string uniformName) {
    std::map<std::string, GLint>::iterator it;
    it = uniformLocations.find(uniformName);
    if(it != uniformLocations.end()) {
        return it->second;
    } else {
        return -1;
    }
}

void Shader::loadUniformLocations() {
    for(auto const& uniform: uniforms) {
        if(uniform->length == 1) {
            if(uniform->type != "struct") {
                uniformLocations.insert(std::pair<std::string, GLint>(uniform->name, getUniformLocation(uniform->name)));
            } else {
                for(auto const& variable: uniform->uniformStruct->getVariables()) {
                    std::string uniformName = uniform->name + "." + variable;
                    uniformLocations.insert(std::pair<std::string, GLint>(uniformName, getUniformLocation(uniformName)));
                }
            }
        } else {
            if(uniform->type != "struct") {
                for(int i = 0; i < uniform->length; i++) {
                    std::string uniformName = uniform->name + "[" + std::to_string(i) + "]";
                    uniformLocations.insert(std::pair<std::string, GLint>(uniformName, getUniformLocation(uniformName)));
                }
            } else {
                for(int i = 0; i < uniform->length; i++) {
                    for(auto const& variable: uniform->uniformStruct->getVariableNames()) {
                        std::string uniformName = uniform->name + "[" + std::to_string(i) + "]." + variable;
                        uniformLocations.insert(std::pair<std::string, GLint>(uniformName, getUniformLocation(uniformName)));
                    }
                }
            }
        }
    }
    validateUniformLocations();
}

void Shader::validateUniformLocations() {
    for(auto const& entry: uniformLocations) {
        if(entry.second == -1) {
            std::cout << "[RenderEngine] Error loading uniform " << entry.first << std::endl;
        }
    }
}

Shader::~Shader() {

}

void Shader::registerAllUniforms() {

}
