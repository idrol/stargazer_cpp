#include "Sphere.h"
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

Sphere::Sphere(PrimitivesUI *primitivesUI): Primitive(primitivesUI, ResourceManager::getInstance().loadTexture("Engine/textures/editor/icons/sphere.png")) {
}

Entity *Sphere::createPrimitiveEntity() {
	Entity *entity = StargazerEngine::getInstance().getActiveLevel()->getEntityManager()->createEntity();
	entity->setName("Sphere " + std::to_string(i++));
	TransformComponent *transformComponent = new TransformComponent(entity); 

	PBRMaterial *mat = new PBRMaterial();
	mat->setAlbedo(glm::vec3(1,1,1));
	mat->setMetallic(0.0F);
	mat->setRoughness(0.0F);

	Model *sphere = shape_util::getSphereModel();
	sphere->setMaterial(mat);

	ModelComponent *modelComponent = new ModelComponent(entity, "sphere");
	modelComponent->setModel(sphere);

	PhysicsComponent *physicsComponent = new PhysicsComponent(entity);
	physicsComponent->configureSphereCollisionShape(1);
	physicsComponent->configureDynamic(transformComponent, 1);

	return entity;
}