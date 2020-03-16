#pragma once

#include <GL/glew.h>
#include "Command.h"
#include <vector>

class Mesh;

class LoadMeshData: public Command {
public:
    LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices, std::vector<GLfloat> &normals, std::vector<GLfloat> &uvs, std::vector<GLfloat> &tangents);
    LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices, std::vector<GLfloat> &normals, std::vector<GLfloat> &uvs);
    LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices, std::vector<GLfloat> &normals);
    LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices);
    LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLfloat> &uvs);
    LoadMeshData(Mesh *mesh, std::vector<GLfloat> &vertices, int vertexLength);
	~LoadMeshData() override;
    void execute() override;
    void loadVertices(std::vector<GLfloat> &vertices, int vertexLength);
    void loadVertices(std::vector<GLfloat> &vertices, int vertexLength, std::vector<GLuint> &indices);
    void loadUVs(std::vector<GLfloat> &uvs);
    void loadNormals(std::vector<GLfloat> &normals);
    void loadTangents(std::vector<GLfloat> &tangents);
    void bindArray();
    void unbindArray();
    GLuint storeDataInAttributeList(GLuint attributeNumber, int coordinateSize, std::vector<GLfloat> &data, GLuint id);
    void bindIndicesBuffer(std::vector<GLuint> &indices);

private:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> uvs;
    std::vector<GLfloat> tangents;
    std::vector<GLuint> indices;
    int vertexLength;
    bool useIndices = false;
    bool useUVs = false;
    bool useNormals = false;
    bool useTangents = false;
    Mesh *mesh;
};