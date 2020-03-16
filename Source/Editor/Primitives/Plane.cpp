#include "Plane.h"
#include "../../Engine/StargazerEngine.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Entity/EntityManager.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/Entity/Component/Component.h"
#include "../../Engine/Entity/Component/PhysicsComponent.h"
#include "../../Engine/Entity/Component/ModelComponent.h"
#include "../../Engine/Entity/Component/TransformComponent.h"
#include "../../RenderEngine/Material/Material.h"
#include "../../RenderEngine/Material/PBRMaterial.h"
#include "../../RenderEngine/Model/Model.h"
#include "../../Util/shape_util.h"
#include "../../RenderEngine/StargazerRenderEngine.h"
#include "../../RenderEngine/Texture/TextureManager.h"
#include "../../ResourceManager/ResourceManager.h"

Plane::Plane(PrimitivesUI *primitivesUI) : Primitive(primitivesUI, ResourceManager::getInstance().loadTexture("Engine/textures/editor/icons/plane.png")) {

}

Entity *Plane::createPrimitiveEntity() {
    Entity *entity = StargazerEngine::getInstance().getActiveLevel()->getEntityManager()->createEntity();
    entity->setName("Plane " + std::to_string(i++));
    TransformComponent *transformComponent = new TransformComponent(entity);

    PBRMaterial *mat = new PBRMaterial();
    mat->setAlbedo(glm::vec3(1,1,1));
    mat->setMetallic(0.0F);
    mat->setRoughness(0.0F);

    Model *plane = shape_util::getQuadModel();
    plane->setMaterial(mat);

    ModelComponent *modelComponent = new ModelComponent(entity, "plane");
    modelComponent->setModel(plane);

    PhysicsComponent *physicsComponent = new PhysicsComponent(entity);
    physicsComponent->configureBoxCollisionShape(glm::vec3(1, 1, 0.1f));
    physicsComponent->configureDynamic(transformComponent, 1);

    return entity;
}
