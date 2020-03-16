//
// Created by Idrol on 23-09-2017.
//

#include "LoadMeshData.h"
#include "../Model/Mesh.h"
#include <iostream>

LoadMeshData::LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices,
                           std::vector<GLfloat> &normals, std::vector<GLfloat> &uvs, std::vector<GLfloat> &tangents) :
                            LoadMeshData(mesh, vertices, vertexLength, indices, normals, uvs) {
    this->tangents = tangents;
    this->useTangents = true;
}

LoadMeshData::LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices, std::vector<GLfloat> &normals, std::vector<GLfloat> &uvs) :
                           LoadMeshData(mesh, vertices, vertexLength, indices, normals) {
    this->uvs = uvs;
    this->useUVs = true;
}

LoadMeshData::LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices, std::vector<GLfloat> &normals) :
                           LoadMeshData(mesh, vertices, vertexLength, indices) {
    this->normals = normals;
    this->useNormals = true;
}

LoadMeshData::LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices) :
                           LoadMeshData(mesh, vertices, vertexLength) {
    this->indices = indices;
    this->useIndices = true;
}

LoadMeshData::LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLfloat> &uvs):
                            LoadMeshData(mesh, vertices, vertexLength){
    this->uvs = uvs;
    this->useUVs = true;
}

LoadMeshData::LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength) {
    this->mesh = mesh;
    this->vertices = vertices;
    this->vertexLength = vertexLength;
}

LoadMeshData::~LoadMeshData() {
	vertices.clear();
	if(useIndices) indices.clear();
	if(useUVs) uvs.clear();
	if(useNormals) normals.clear();
	if(useTangents) tangents.clear();
}

void LoadMeshData::execute() {
    bindArray();
    if(!useIndices) {
        loadVertices(vertices, vertexLength);
		//std::vector<GLfloat>().swap(vertices);
    } else {
        loadVertices(vertices, vertexLength, indices);
		//std::vector<GLfloat>().swap(vertices);
		//std::vector<GLuint>().swap(indices);
    }

    if(useUVs) {
        loadUVs(uvs);
		//std::vector<GLfloat>().swap(uvs);
    }

    if(useNormals) {
        loadNormals(normals);
		//std::vector<GLfloat>().swap(normals);
    }

    if(useTangents) {
        loadTangents(tangents);
		//std::vector<GLfloat>().swap(tangents);
    }

    unbindArray();
}

void LoadMeshData::loadVertices(std::vector<GLfloat> &vertices, int vertexLength) {
    mesh->vertexID = storeDataInAttributeList(0, vertexLength, vertices, mesh->vertexID);
    mesh->vertexCount = vertices.size()/vertexLength;
    mesh->missingIndexBuffer = true;
}

void LoadMeshData::loadVertices(std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices) {
    bindIndicesBuffer(indices);
    mesh->vertexID = storeDataInAttributeList(0, vertexLength, vertices, mesh->vertexID);
    mesh->vertexCount = indices.size();
}

void LoadMeshData::loadUVs(std::vector<GLfloat> &uvs) {
    mesh->uvID = storeDataInAttributeList(1, 2, uvs, mesh->uvID);
}

void LoadMeshData::loadNormals(std::vector<GLfloat> &normals) {
    mesh->normalID = storeDataInAttributeList(2, 3, normals, mesh->normalID);
}

void LoadMeshData::loadTangents(std::vector<GLfloat> &tangents) {
    mesh->tangentID = storeDataInAttributeList(3, 3, tangents, mesh->tangentID);
}

void LoadMeshData::bindArray() {
    glBindVertexArray(mesh->vaoID);
}

void LoadMeshData::unbindArray() {
    glBindVertexArray(0);
}

GLuint LoadMeshData::storeDataInAttributeList(GLuint attributeNumber, int coordinateSize, std::vector<GLfloat> &data, GLuint id) {
    GLuint vboID = 0;
    //if(id == 0) {
        GLuint buffers;
        glGenBuffers(1, &buffers);
        vboID = buffers;
    //} else {
    //    vboID = id;
    //}
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attributeNumber);
    return vboID;
}

void LoadMeshData::bindIndicesBuffer(std::vector<GLuint> &indices) {
    //if(mesh->indexID == 0) {
        GLuint buffers;
        glGenBuffers(1, &buffers);
        mesh->indexID = buffers;
    //}
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}
