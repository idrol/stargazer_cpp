#include "ModelComponentFormatter.h"
#include "../MeshFormatter.h"
#include "../../../../Engine/Entity/Component/Component.h"
#include "../../../../Engine/Entity/Component/ModelComponent.h"
#include "../../../../RenderEngine/Model/Model.h"

nlohmann::json ModelComponentFormatter::serialize(Component *component) {

    ModelComponent *modelComponent = (ModelComponent*)component;
    Model *model = modelComponent->getModel();
    nlohmann::json meshesJson = {};
    for(auto & mesh: model->getMeshes()) {
        nlohmann::json meshJson = MeshFormatter::serialize(mesh);
        if(!meshJson.empty()) {
            meshesJson.push_back(meshJson);
        }
    }
    nlohmann::json componentJson = {
            {"type", "ModelComponent"},
            {"name", component->getName()},
            {"meshes", meshesJson}
    };
    return componentJson;
}

void ModelComponentFormatter::deserialize(nlohmann::json componentData, Entity *entity) {
    ModelComponent *modelComponent = new ModelComponent(entity, componentData["name"]);
    nlohmann::json meshesJson = componentData["meshes"];
    Model *model = new Model();
    for(auto & mesh: meshesJson) {
        MeshFormatter::deserialize(mesh, model);
    }
    modelComponent->setModel(model);
}
