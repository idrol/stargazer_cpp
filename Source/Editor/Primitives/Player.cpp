#include "Player.h"
#include "../../Engine/StargazerEngine.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Entity/EntityManager.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/Entity/Component/Component.h"
#include "../../Engine/Entity/Component/TransformComponent.h"
#include "../../Engine/Entity/Component/CameraComponent.h"
#include "../../Engine/Entity/Component/SimpleKeyboardComponent.h"
#include "../../RenderEngine/StargazerRenderEngine.h"
#include "../../RenderEngine/Texture/TextureManager.h"
#include "../../ResourceManager/ResourceManager.h"

Player::Player(PrimitivesUI *primitivesUI) : Primitive(primitivesUI, ResourceManager::getInstance().loadTexture("Engine/textures/editor/icons/player.png")) {

}

Entity *Player::createPrimitiveEntity() {
    Entity *entity = StargazerEngine::getInstance().getActiveLevel()->getEntityManager()->createEntity();
    entity->setName("Player");
    TransformComponent *transform = new TransformComponent(entity);
    CameraComponent *cameraComponent = new CameraComponent(entity, 75, 0.0001F, 10000.0F);

    SimpleKeyboardComponent *keyboardComponent = new SimpleKeyboardComponent(entity);

    return entity;
}