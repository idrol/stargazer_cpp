#include "GL/glew.h"
#include "DeleteMesh.h"
#include <iostream>
#include "../Model/Mesh.h"

DeleteMesh::DeleteMesh(Mesh *mesh) {
    this->mesh = mesh;
}

void DeleteMesh::execute() {
    GLuint vaoIDs[1] = {mesh->vaoID};
    glDeleteVertexArrays(1, vaoIDs);
    std::cout << "[RenderEngine] Deleting mesh pointer with id " << vaoIDs[0] << "." << std::endl;
	delete mesh;
}