//
// Created by Idrol on 05-10-2017.
//

#include "skybox_util.h"
#include "../RenderEngine/Texture/TextureLoader.h"
#include "../RenderEngine/Texture/Texture.h"
#include "../RenderEngine/Model/Mesh.h"
#include "../RenderEngine/Model/Model.h"
#include "../RenderEngine/Material/Material.h"
#include "../RenderEngine/Material/SkyboxMaterial.h"
#include "../RenderEngine/Command/LoadMeshData.h"
#include "../RenderEngine/RenderEngine.h"

std::vector<GLfloat> skybox_util::getSkybox(float SIZE) {
    return std::vector<GLfloat>{
            -SIZE,  SIZE, -SIZE,
            -SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

            -SIZE,  SIZE, -SIZE,
            SIZE,  SIZE, -SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
            SIZE, -SIZE,  SIZE
    };
}

Texture *skybox_util::createCubeMapTexture(std::string left, std::string right, std::string top, std::string bottom,
                                           std::string back, std::string front) {
    std::vector<std::string> texture_files{
            left,
            right,
            top,
            bottom,
            back,
            front
    };
    return new Texture(GL_TEXTURE_CUBE_MAP, TextureLoader::loadCubeMap(texture_files), "");
}

Model *skybox_util::createSkyboxModel(std::string textureName, float size) {
	SkyboxMaterial *skyboxMaterial = new SkyboxMaterial();
	skyboxMaterial->setSkyBoxTextureWithName(textureName);

	Mesh *skybox = new Mesh(customPrimitive);
	std::vector<GLfloat> skybox_verts = getSkybox(size);
	LoadMeshData *loadMeshData = new LoadMeshData(skybox, skybox_verts, 3);
	RenderEngine::getInstance().addCommand(loadMeshData);
	skybox->setMaterial(skyboxMaterial);

	Model *skyboxModel = new Model();
	skyboxModel->setMaterial(skyboxMaterial);
	skyboxModel->addMesh(skybox);
	return skyboxModel;
}

Mesh *skybox_util::getSkyboxMesh() {
	std::vector<GLfloat> vertices = getSkybox(1);
	Mesh *mesh = new Mesh(skybox);
	auto *loadMeshData = new LoadMeshData(mesh, vertices, 3);
	RenderEngine::getInstance().addCommand(loadMeshData);
	return mesh;
}
