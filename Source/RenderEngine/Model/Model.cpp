#include <GL/glew.h>
#include "Model.h"
#include "Mesh.h"
#include "Transform.h"
#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"
#include "../Shaders/ObjectOutlineShader.h"
#include <iostream>
#include <GLM/mat4x4.hpp>

Model::~Model() {
	for(auto & it: meshes) {
		it->deleteMesh();
	}
}

Transform* Model::getTransform() {
    return transform;
}

void Model::setPositionControl(Transform *transform) {
    positionControl = transform;
}

void Model::setRotationControl(Transform *transform) {
    rotationControl = transform;
}

void Model::setScaleControl(Transform *transform) {
    scaleControl = transform;
}

void Model::setPosition(glm::vec3 position) {
    positionControl->translate(position);
    transformMatrix = transform->compileTransform();
}

void Model::setRotation(glm::vec3 rotation) {
    rotationControl->rotate(rotation);
    transformMatrix = transform->compileTransform();
}

void Model::setScale(glm::vec3 scale) {
    scaleControl->scale(scale);
    transformMatrix = transform->compileTransform();
}

void Model::setVisible(bool visible) {
    this->visible = visible;
}

bool Model::isVisible() {
    return visible;
}

void Model::draw() {
    if(wireframe || !cullFace) {
        glDisable(GL_CULL_FACE);
    }
    if(wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	if(drawOutline) {
		glStencilMask(0xFF);
	}
    for(auto & mesh: meshes) {
        mesh->draw(transformMatrix);
    }
	if(drawOutline) {
		ObjectOutlineShader *outlineShader = (ObjectOutlineShader*)ShaderManager::getShader("outlineShader");
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		//glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		outlineShader->start();
		outlineShader->loadTransformationMatrix(transformMatrix);
		for(auto & mesh: meshes) {
			mesh->drawWithoutMaterial();
		}
		outlineShader->stop();
		glEnable(GL_CULL_FACE);
		//glEnable(GL_DEPTH_TEST);
	}

    if(wireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if(wireframe || !cullFace) {
		glEnable(GL_CULL_FACE);
	};
}

void Model::addMesh(Mesh *mesh) {
    meshes.push_back(mesh);
}

Model::Model() {
    transform = new Transform(this);
    positionControl = transform;
    rotationControl = transform;
    scaleControl = transform;
    transformMatrix = transform->compileTransform();
}

void Model::setMaterial(Material *material) {
    this->material = material;
    for(auto & mesh: meshes) {
        mesh->setMaterial(material);
    }
}

Mesh *Model::getMesh(int i) {
    return meshes[i];
}

std::vector<Mesh*> Model::getMeshes() {
	return meshes;
}

void Model::enableOutline(bool outline) {
	this->drawOutline = outline;
}

Material *Model::getMaterial() {
    return material;
}
