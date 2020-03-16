#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>

class Texture;
class Model;
class Mesh;

class skybox_util {
public:
    static std::vector<GLfloat> getSkybox(float SIZE);
    static Texture* createCubeMapTexture(std::string left, std::string right, std::string top, std::string bottom, std::string back, std::string front);
	static Mesh *getSkyboxMesh();
	static Model *createSkyboxModel(std::string texture, float size);
};
