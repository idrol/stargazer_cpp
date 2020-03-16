//
// Created by Idrol on 23-04-2018.
//

#include "CAPIEntity.h"
#include "../Engine/Entity/Entity.h"
#include "../Engine/StargazerEngine.h"
#include "../Engine/Level/Level.h"
#include "../Engine/Entity/EntityManager.h"

extern "C" {

    CEntity createEntity() {
        Entity *entity = StargazerEngine::getInstance().getActiveLevel()->getEntityManager()->createEntity();
        return reinterpret_cast<CEntity>(entity);
    }

    void setEntityName(CEntity entity, const char *name) {
        std::string test = std::string(name);
        reinterpret_cast<Entity*>(entity)->setName(test, false);
    }

    char *getEntityName(CEntity entity) {
        Entity *entity1 = reinterpret_cast<Entity*>(entity);
        const char *name = entity1->getName().c_str();
        ULONG ulSize = strlen(name)+ sizeof(char);
        char * pszReturn = NULL;

        pszReturn = (char*)::CoTaskMemAlloc(ulSize);
        strcpy(pszReturn, name);
        return pszReturn;
    }

    void addEntityComponent(CEntity entity, CComponent component) {
        reinterpret_cast<Entity*>(entity)->addComponent(reinterpret_cast<Component*>(component));
    }

    CComponent getEntityComponent(CEntity entity, MonoString *id) {
        return reinterpret_cast<CComponent>(reinterpret_cast<Entity*>(entity)->getComponent(mono_string_to_utf8(id)));
    }

    void removeEntityComponent(CEntity entity, MonoString *id) {
        reinterpret_cast<Entity*>(entity)->removeComponent(mono_string_to_utf8(id));
    }

    void selectEntity(CEntity entity) {
        reinterpret_cast<Entity*>(entity)->select();
    }

    void deselectEntity(CEntity entity) {
        reinterpret_cast<Entity*>(entity)->deselect();
    }

}

