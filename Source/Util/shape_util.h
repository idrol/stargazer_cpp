#pragma once

class Mesh;
class Model;

class shape_util {
public:
    static Mesh *getSphereMesh();
    static Model *getSphereModel();
    static Mesh *getQuadMesh();
    static Model *getQuadModel();
    static Mesh *getCubeMesh();
    static Model *getCubeModel();
};
