#pragma once

#include <map>
#include <string>
#include <vector>
#include <GLM/glm.hpp>

class Shader;
class ILightShader;

class ShaderManager {
public:
    static void registerDefaults();
    static void reloadProjectionMatrix(glm::mat4 projectionMatrix);
    static void reloadViewMatrix(glm::mat4 viewMatrix);
    static void saveCamPos(glm::vec3 camPos);
    static void compileLights();
    static void registerShader(std::string name, Shader *shader);
    static Shader* getShader(std::string name);
    static std::map<std::string, Shader*> shaders;
    static std::vector<ILightShader*> lightShaders;
};
