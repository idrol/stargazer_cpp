#include "PointLightComponentFormatter.h"
#include "../../../../Engine/Entity/Component/PointLightComponent.h"
#include "../../../../RenderEngine/Light/Light.h"
#include "../../../../RenderEngine/Light/PointLight.h"

nlohmann::json PointLightComponentFormatter::serialize(Component *component) {
    PointLightComponent *pointLightComponent = (PointLightComponent*)component;
    PointLight *pointLight = pointLightComponent->getPointLight();
    nlohmann::json componentJson = {
            {"type", pointLightComponent->getType()},
            {"name", pointLightComponent->getName()},
            {"color", {pointLight->getColor().x, pointLight->getColor().y, pointLight->getColor().z}},
            {"intensity", pointLight->getIntensity()}
    };
    return componentJson;
}

void PointLightComponentFormatter::deserialize(nlohmann::json componentData, Entity *entity) {
    PointLightComponent *pointLightComponent = new PointLightComponent(entity, componentData["name"]);
    PointLight *pointLight = new PointLight(glm::vec3(0,0,0), glm::vec3(componentData["color"][0], componentData["color"][1], componentData["color"][2]), componentData["intensity"]);
    pointLightComponent->setPointLight(pointLight);
}
