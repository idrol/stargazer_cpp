#define _USE_MATH_DEFINES
#include <vector>
#include <GL/glew.h>
#include <cmath>
#include "shape_util.h"
#include "../RenderEngine/Model/Mesh.h"
#include "../RenderEngine/Model/Model.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/Command/LoadMeshData.h"
#include "vector_util.h"
#include <iostream>

Mesh *shape_util::getSphereMesh() {
    float radius = 1;
    unsigned int rings = 60;
    unsigned int sectors = 60;
    Mesh *mesh = new Mesh(sphere);
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;
    std::vector<GLfloat> vertices(rings * sectors * 3);
    std::vector<GLfloat> normals(rings * sectors * 3);
    std::vector<GLfloat> texcoords(rings * sectors * 2);
    std::vector<GLuint> indices(rings * sectors * 6);
    std::vector<GLfloat>::iterator v = vertices.begin();
    std::vector<GLfloat>::iterator n = normals.begin();
    std::vector<GLfloat>::iterator t = texcoords.begin();
    for(r = 0; r < rings; r++) {
        for(s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2*M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2*M_PI * s * S) * sin(M_PI * r * R);

            *t++ = s*S;
            *t++ = r*R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = x;
            *n++ = y;
            *n++ = z;
        }
    }
    std::vector<GLuint>::iterator i = indices.begin();
    for(r = 0; r < rings-1; r++) {
        for(s = 0; s < sectors-1; s++) {

            *i++ = r * sectors + (s+1);
            *i++ = r * sectors + s;
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = r * sectors + s;
            *i++ = (r+1) * sectors + s;


            /**i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
            *i++ = (r+1) * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);*/
        }
    }
    //vector_util::printVector(normals);
    LoadMeshData *cmd = new LoadMeshData(mesh, vertices, 3, indices, normals, texcoords);
    RenderEngine::getInstance().addCommand(cmd);
    return mesh;
}

Mesh *shape_util::getQuadMesh() {
    std::vector<GLfloat> vertices {
            -1, 1, 0,
            -1, -1, 0,
            1, 1, 0,
            1, -1, 0
    };

    std::vector<GLuint> indices {
            0, 1, 2,
            2, 1, 3
    };

    std::vector<GLfloat> texcoords {
            0, 1,
            0, 0,
            1, 1,
            1, 0,
    };
    std::vector<GLfloat> normals {
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1
    };
    Mesh *mesh = new Mesh(plane);
    RenderEngine::getInstance().addCommand(new LoadMeshData(mesh, vertices, 3, indices, normals, texcoords));
    return mesh;
}

Model *shape_util::getQuadModel() {
    Mesh *mesh = getQuadMesh();
    Model *model = new Model();
    model->addMesh(mesh);
    return model;
}

Model *shape_util::getSphereModel() {
    Mesh *mesh = getSphereMesh();
    Model *model = new Model();
    model->addMesh(mesh);
    return model;
}

Mesh *shape_util::getCubeMesh() {
    std::vector<GLfloat> uvs{
        1, 0,
        0, 0,
        0, 1,
        1, 1,

        1, 0,
        0, 0,
        0, 1,
        1, 1,

        1, 0,
        0, 1,
        0, 0,
        1, 1,

        1, 0,
        0, 0,
        0, 1,
        1, 1,

        1, 0,
        0, 0,
        0, 1,
        1, 1,

        1, 0,
        0, 1,
        0, 0,
        1, 1,
    };
    std::vector<GLuint> indices{
            // Right
            0, 1, 2,
            0, 2, 3,

            // Front
            4, 5, 6,
            7, 4, 6,

            // Right
            8, 9, 10,
            9, 8, 11,

            // Back
            12, 13, 14,
            14, 15, 12,

            // Top
            16, 17, 18,
            16, 18, 19,

            // Bottom
            20, 21, 22,
            20, 23, 21
    };

    std::vector<GLfloat> vertices{
            // Right
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,

            // Front
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,

            // Right
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,

            // Back
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,

            // Top
            1.0f, 1.0f, 1.0f, // 6
            1.0f, 1.0f,-1.0f, // 4
            -1.0f, 1.0f,-1.0f, // 3
            -1.0f, 1.0f, 1.0f, // 2

            // Bottom
            1.0f,-1.0f, 1.0f, // 7
            -1.0f,-1.0f,-1.0f, // 0
            1.0f,-1.0f,-1.0f, // 5
            -1.0f,-1.0f, 1.0f, // 1
    };

    std::vector<GLfloat> normals{
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,

            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
    };



    Mesh *mesh = new Mesh(cube);
    //RenderEngine::getInstance().addCommand(new LoadMeshData(mesh, vertices, 3));
    RenderEngine::getInstance().addCommand(new LoadMeshData(mesh, vertices, 3, indices, normals, uvs));

    return mesh;
}

Model *shape_util::getCubeModel() {
    Model *model = new Model();
    model->addMesh(getCubeMesh());
    return model;
}
