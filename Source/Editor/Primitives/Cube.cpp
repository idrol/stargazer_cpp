#include "Cube.h"
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

Cube::Cube(PrimitivesUI *primitivesUI) : Primitive(primitivesUI, ResourceManager::getInstance().loadTexture("Engine/textures/editor/icons/cube.png")) {

}

Entity *Cube::createPrimitiveEntity() {
    Entity *entity = StargazerEngine::getInstance().getActiveLevel()->getEntityManager()->createEntity();
    entity->setName("Cube " + std::to_string(i++));
    TransformComponent *transformComponent = new TransformComponent(entity);

    PBRMaterial *mat = new PBRMaterial();
    mat->setAlbedo(glm::vec3(1,1,1));
    mat->setMetallic(0.0F);
    mat->setRoughness(0.0F);

    Model *cube = shape_util::getCubeModel();
    cube->setMaterial(mat);

    ModelComponent *modelComponent = new ModelComponent(entity, "cube");
    modelComponent->setModel(cube);

    PhysicsComponent *physicsComponent = new PhysicsComponent(entity);
    physicsComponent->configureBoxCollisionShape(glm::vec3(1,1,1));
    physicsComponent->configureDynamic(transformComponent, 1);

    return entity;
}
