#pragma once

#include <GL/glew.h>
#include <map>
#include <list>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include "preprocessor/Uniform.h"

class Shader {
public:
    explicit Shader(std::string shaderFile);
    virtual ~Shader();
    void init();
    virtual void registerAllUniforms();
    virtual void preInit() {};
    bool isEnableProjectionMatrix();
    void setEnableProjectionMatrix(bool enableProjectionMatrix);
    bool isEnableViewMatrix();
    void setEnableViewMatrix(bool enableViewMatrix);
    bool isEnableTransformationMatrix();
    void setEnableTransformationMatrix(bool enableTransformationMatrix);
    void addUses() {uses++;};
    int getUses() {return uses;};
    void registerUniform(Uniform *uniform) {uniforms.push_back(uniform);};
    void unregisterUniform(std::string uniform);
    virtual void getAllUniformLocations() {};
    virtual void loadTextureAddresses() {};
    GLint getUniformLocation(std::string uniform);
    void start();
    void stop();
    void loadInt(GLint location, GLint value);
    virtual void bindAttributes() {};
    void bindAttribute(GLuint location, std::string variable);
    void loadFloat(GLint location, GLfloat value);
    void loadVector3f(GLint location, glm::vec3 value);
    void loadVector4f(GLint location, glm::vec4 value);
    void loadBool(GLint location, bool value);
    void loadInt(std::string uniform, GLint value);
    void loadFloat(std::string uniform, GLfloat value);
    void loadVector3f(std::string uniform, glm::vec3 value);
    void loadVector4f(std::string uniform, glm::vec4 value);
    void loadBool(std::string uniform, bool value);
    void loadMatrix(GLint location, glm::mat4 matrix);
    virtual void loadTransformationMatrix(glm::mat4 matrix);
    virtual void loadProjectionMatrix(glm::mat4 matrix);
    virtual void loadViewMatrix(glm::mat4 matrix);
    GLint getStoredUniformLocation(std::string uniformName);
    std::list<Uniform*> getUniforms() {return uniforms;};
protected:
    bool enableProjectionMatrix = true;
    bool enableViewMatrix = true;
    bool enableTransformationMatrix = true;
    std::map<std::string, GLint> uniformLocations;
    std::list<Uniform*> uniforms;
    int uses = 0;

    void loadUniformLocations();
private:
    std::string shaderFile;
    GLuint programID;
    void validateUniformLocations();
};