#include "Mesh.h"
#include "../RenderEngine.h"
#include "../Command/CreateMesh.h"
#include "../Command/DeleteMesh.h"
#include "../Material/Material.h"
#include "../Shaders/Shader.h"
#include <iostream>

Mesh::Mesh(std::string path): Mesh() {
	meshType = asset;
	this->path = path;
}

Mesh::Mesh(MeshPrimitiveType meshPrimitiveType): Mesh() {
	meshType = primitive;
	this->meshPrimitiveType = meshPrimitiveType;
}

Mesh::Mesh() {
    RenderEngine::getInstance().addCommand(new CreateMesh(this));
}

void Mesh::deleteMesh() {
    RenderEngine::getInstance().addCommand(new DeleteMesh(this));
}

void Mesh::setMaterial(Material *material) {
    this->material = material;
}

void Mesh::draw(glm::mat4 transform) {
    if(material != nullptr && intiailized) {
		material->apply();
		if(material->getShader()->isEnableTransformationMatrix()) {
			material->getShader()->loadTransformationMatrix(transform);
		}
		drawWithoutMaterial();
        material->getShader()->stop();
    }
}

void Mesh::drawWithoutMaterial() {
	glBindVertexArray(vaoID);

	if(missingIndexBuffer) {
		glDrawArrays(renderMode, 0, vertexCount);
	} else {
		glDrawElements(renderMode, vertexCount, GL_UNSIGNED_INT, (void*)0);
	}

	glBindVertexArray(0);
}

Material *Mesh::getMaterial() {
    return material;
}


