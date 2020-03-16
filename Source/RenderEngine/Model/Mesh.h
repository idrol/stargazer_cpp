#pragma once

#include <GL/glew.h>
#include "Transform.h"
#include <string>

class Material;

enum MeshType {primitive, asset, custom}; // Custom mesh has no supported saving.
enum MeshPrimitiveType {sphere, cube, plane, skybox, customPrimitive}; // Custom primitive triggers type to be custom disabling all mesh saving.

class Mesh {
public:
	Mesh(std::string path);
	Mesh(MeshPrimitiveType meshPrimitiveType);
    void setMaterial(Material *material);
    Material *getMaterial();
    void draw(glm::mat4 transform);
	void drawWithoutMaterial();
	void deleteMesh();

    GLenum renderMode = GL_TRIANGLES;
    GLuint vaoID, vertexID, normalID, indexID, uvID, tangentID;
    int vertexCount;
    bool missingIndexBuffer = false;
    bool intiailized = false;
	MeshType getMeshType() {return meshType;};
	MeshPrimitiveType getMeshPrimitiveType() {return meshPrimitiveType;};
	std::string getPath() {return path;};

protected:
    Material *material = nullptr;
	MeshType meshType;
	MeshPrimitiveType meshPrimitiveType;
	std::string path;

private:
	Mesh();
};