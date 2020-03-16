#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model;
class Mesh;

class ModelLoader {
public:
    static void loadModel(Model *model, std::string path, std::string localPath);
    static void processNode(Model *model, aiNode *node, const aiScene *scene, std::string path);
    static Mesh *processMesh(aiMesh *mesh, const aiScene *scene, std::string path);
};
