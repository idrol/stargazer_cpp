#include "Component.h"
#include "../Entity.h"

Component::Component(Entity *entity, std::string id, std::string type)  {
    this->id = id;
    this->type = type;
    entity->addComponent(this);
}