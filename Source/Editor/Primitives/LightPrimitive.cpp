#include "LightPrimitive.h"
#include "../../Engine/StargazerEngine.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Entity/EntityManager.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/Entity/Component/Component.h"
#include "../../Engine/Entity/Component/PointLightComponent.h"
#include "../../Engine/Entity/Component/TransformComponent.h"
#include "../../RenderEngine/StargazerRenderEngine.h"
#include "../../RenderEngine/Texture/TextureManager.h"
#include "../../ResourceManager/ResourceManager.h"

LightPrimitive::LightPrimitive(PrimitivesUI *primitivesUI): Primitive(primitivesUI, ResourceManager::getInstance().loadTexture("Engine/textures/editor/icons/light.png")) {

}

Entity *LightPrimitive::createPrimitiveEntity() {
	Entity *entity = StargazerEngine::getInstance().getActiveLevel()->getEntityManager()->createEntity();
	entity->setName("Light " + std::to_string(i++));
	TransformComponent *transformComponent = new TransformComponent(entity);
	PointLightComponent *lightComponent = new PointLightComponent(entity, "light");
	lightComponent->setPointLight(new PointLight(glm::vec3(0,0,0), glm::vec3(1,1,1), 300));


	return entity;
}