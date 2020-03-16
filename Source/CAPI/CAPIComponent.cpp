#include "CAPIComponent.h"

#include "../Engine/Entity/Entity.h"
#include "../Engine/Entity/Component/Component.h"
#include <string>

char *getComponentName(CComponent component) {
    Component *component1 = reinterpret_cast<Component*>(component);
    const char *name = component1->getName().c_str();
    ULONG ulSize = strlen(name) + sizeof(char);
    char * pszReturn = NULL;

    pszReturn = (char*)::CoTaskMemAlloc(ulSize);
    strcpy(pszReturn, name);
    return pszReturn;
}

/*
void setComponentName(CComponent component, const char *name) {
    std::string tmp = std::string(name);
    reinterpret_cast<Component*>(component).set;
}*/

void setComponentEntity(CComponent component, CEntity entity) {
    Entity *entity1 = reinterpret_cast<Entity*>(entity);
    Component *component1 = reinterpret_cast<Component*>(component);
    component1->setEntity(entity1);
}
