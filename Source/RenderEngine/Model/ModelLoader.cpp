//
// Created by Idrol on 09-10-2017.
//

#include "ModelLoader.h"
#include "Model.h"
#include "Mesh.h"
#include "../Texture/Texture.h"
#include "../RenderEngine.h"
#include "../Command/LoadMeshData.h"
#include <iostream>
#include <vector>
#include "../../ResourceManager/ResourceManager.h"

void ModelLoader::loadModel(Model *model, std::string path, std::string localPath) {
    Assimp::Importer import = *new Assimp::Importer();
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate );

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        exit(-1);
    }

    processNode(model, scene->mRootNode, scene, localPath);
}

void ModelLoader::processNode(Model *model, aiNode *node, const aiScene *scene, std::string path) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        Mesh *engineMesh = processMesh(mesh, scene, path);
        engineMesh->setMaterial(model->getMaterial());
        model->addMesh(engineMesh);
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(model, node->mChildren[i], scene, path);
    }
}

Mesh *ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene, std::string path) {
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> uvs;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vector = mesh->mVertices[i];
        positions.push_back(vector.x);
        positions.push_back(vector.y);
        positions.push_back(vector.z);
        aiVector3D normal = mesh->mNormals[i];
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
        if(mesh->mTextureCoords[0]) {
            aiVector3D uv = mesh->mTextureCoords[0][i];
            uvs.push_back(uv.x);
            uvs.push_back(uv.y);
        } else {
            uvs.push_back(0);
            uvs.push_back(0);
        }
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    Mesh *mesh1 = new Mesh(path);
    RenderEngine::getInstance().addCommand(new LoadMeshData(mesh1, positions, 3, indices, normals, uvs));
    return mesh1;
}
