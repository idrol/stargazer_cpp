#include "CameraComponentFormatter.h"
#include "../../../../Engine/Entity/Entity.h"
#include "../../../../Engine/Entity/Component/TransformComponent.h"
#include "../../../../Engine/Entity/Component/CameraComponent.h"
#include "../../../../RenderEngine/Camera/Camera.h"

nlohmann::json CameraComponentFormatter::serialize(Component *component) {
    CameraComponent *cameraComponent = (CameraComponent*)component;
    Camera *camera = cameraComponent->getCamera();

    nlohmann::json componentData = {
            {"type", cameraComponent->getType()},
            {"name", cameraComponent->getName()},
            {"fov", camera->getFov()},
            {"far", camera->getFar()},
            {"near", camera->getNear()}
    };
    return componentData;
}

void CameraComponentFormatter::deserialize(nlohmann::json componentData, Entity *entity) {
    CameraComponent *cameraComponent = new CameraComponent(entity, componentData["fov"], componentData["near"], componentData["far"]);
}
