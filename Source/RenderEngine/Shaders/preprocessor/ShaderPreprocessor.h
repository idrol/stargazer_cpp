#pragma once

#include <string>
#include <vector>
#include <list>
#include <GL/glew.h>

class ShaderSource;
class Shader;

class ShaderPreprocessor {
public:
    static const int shaderVersion = 400;
    static ShaderSource* loadShader(std::string path, Shader *shader);
    static void preprocessShader(ShaderSource *shaderSource);
    static void cacheShader(std::string shader, ShaderSource *shaderSource, std::string fileExtension);
    static std::string buildShader(std::vector<std::string> sourceLines);
    static void generateUniforms(ShaderSource *shaderSource, std::vector<std::string> &vertexSourceLines, std::vector<std::string> &fragmentSourceLines);
    static void splitShaderSource(ShaderSource *shaderSource, std::vector<std::string> &vertexSourceLines, std::vector<std::string> &fragmentSourceLines);
    static void readShader(ShaderSource *shaderSource, std::vector<std::string> &sourceLines, std::vector<std::string>::iterator lineIterator); // prob redisgn
    static GLuint createShaderProgram(ShaderSource *shaderSource);
    static GLuint compileShader(std::string source, GLenum shaderType);
    static std::string getNameFromPath(std::string path);

private:
    static std::string getMD5HashForString(std::string data);

};
