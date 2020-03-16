#include "SkyboxPrimitive.h"
#include "../../Engine/StargazerEngine.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Entity/EntityManager.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/Entity/Component/Component.h"
#include "../../Engine/Entity/Component/PhysicsComponent.h"
#include "../../Engine/Entity/Component/ModelComponent.h"
#include "../../Engine/Entity/Component/TransformComponent.h"
#include "../../RenderEngine/Material/Material.h"
#include "../../RenderEngine/Material/SkyboxMaterial.h"
#include "../../RenderEngine/Model/Model.h"
#include "../../Util/shape_util.h"
#include "../../RenderEngine/StargazerRenderEngine.h"
#include "../../RenderEngine/Texture/TextureManager.h"
#include "../../ResourceManager/ResourceManager.h"

SkyboxPrimitive::SkyboxPrimitive(PrimitivesUI *primitivesUI): Primitive(primitivesUI, ResourceManager::getInstance().loadTexture("Engine/textures/editor/icons/cube.png")){

}

Entity *SkyboxPrimitive::createPrimitiveEntity() {
    Entity *entity = StargazerEngine::getInstance().getActiveLevel()->getEntityManager()->createEntity();
    entity->setName("Sky Box");
    TransformComponent *transformComponent = new TransformComponent(entity);

    SkyboxMaterial *material = new SkyboxMaterial();

    Mesh *mesh = skybox_util::getSkyboxMesh();

    Model *cube = new Model();
    cube->addMesh(mesh);
    cube->setMaterial(material);
    cube->disableCullFace();

    ModelComponent *modelComponent = new ModelComponent(entity, "skybox");
    modelComponent->setModel(cube);

    return entity;
}
