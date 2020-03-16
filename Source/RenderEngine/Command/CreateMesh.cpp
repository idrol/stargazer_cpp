#include "GL/glew.h"
#include "CreateMesh.h"
#include "../Model/Mesh.h"
#include <iostream>


CreateMesh::CreateMesh(Mesh *mesh)
{
	this->mesh = mesh;
}


void CreateMesh::execute() {
	GLuint vaoIDs;
	glGenVertexArrays(1, &vaoIDs);
	std::cout << "[RenderEngine] " << "Creating vertex array object id " << vaoIDs << std::endl;
	mesh->vaoID = vaoIDs;
	mesh->intiailized = true;
}


CreateMesh::~CreateMesh()
{
}
