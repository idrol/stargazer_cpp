#include "MeshFormatter.h"
#include "MaterialFormatManager.h"
#include "../../../RenderEngine/Model/Mesh.h"
#include "../../../Util/shape_util.h"
#include "../../../RenderEngine/Model/Model.h"
#include "../../../Util/skybox_util.h"

nlohmann::json MeshFormatter::serialize(Mesh *mesh) {
    std::string type = "";
    if(mesh->getMeshType() == primitive) {
        type = "primitive";
        std::string primitiveType = "";

        if(mesh->getMeshPrimitiveType() == sphere) {
            primitiveType = "sphere";
        } else if(mesh->getMeshPrimitiveType() == cube) {
            primitiveType = "cube";
        } else if(mesh->getMeshPrimitiveType() == plane) {
            primitiveType = "plane";
        } else if(mesh->getMeshPrimitiveType() == skybox) {
            primitiveType = "skybox";
        } else {
            return nlohmann::json();
        }
        MaterialFormatManager *materialFormatManager = new MaterialFormatManager();
        nlohmann::json meshJson = {
                {"type", type},
                {"primitive_type", primitiveType},
                {"material", materialFormatManager->serialize(mesh->getMaterial())}
        };
        delete materialFormatManager;
        return meshJson;
    } else if(mesh->getMeshType() == asset) {
        type = "asset";
        MaterialFormatManager *materialFormatManager = new MaterialFormatManager();
        nlohmann::json meshJson = {
                {"type", type},
                {"path", mesh->getPath()},
                {"material", materialFormatManager->serialize(mesh->getMaterial())}
        };
        delete materialFormatManager;
        return meshJson;
    } else {
        // Type was custom not supported for saving and loading
        return nlohmann::json();
    }
}

void MeshFormatter::deserialize(nlohmann::json meshData, Model *model) {
    std::string type = meshData["type"];
    if(type == "primitive") {
        std::string primitive_type = meshData["primitive_type"];
        MaterialFormatManager *materialFormatManager = new MaterialFormatManager();
        if(primitive_type == "sphere") {
            Mesh *mesh = shape_util::getSphereMesh();
            nlohmann::json materialData = meshData["material"];
            materialFormatManager->deserialize(materialData, mesh);
            model->addMesh(mesh);
        } else if(primitive_type == "cube") {
            Mesh *mesh = shape_util::getCubeMesh();
            nlohmann::json materialData = meshData["material"];
            materialFormatManager->deserialize(materialData, mesh);
            model->addMesh(mesh);
        } else if(primitive_type == "plane") {
            Mesh *mesh = shape_util::getQuadMesh();
            nlohmann::json materialData = meshData["material"];
            materialFormatManager->deserialize(materialData, mesh);
            model->addMesh(mesh);
        } else if(primitive_type == "skybox") {
            Mesh *mesh = skybox_util::getSkyboxMesh();
            nlohmann::json materialData = meshData["material"];
            materialFormatManager->deserialize(materialData, mesh);
            model->addMesh(mesh);
        }
        delete materialFormatManager;
    } else if(type == "asset") {
        // TODO support custom models.
    }
}
