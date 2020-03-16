//
// Created by Idrol on 21-04-2018.
//

#pragma once

#include <mono/metadata/object.h>
#include <mono/metadata/debug-helpers.h>
#include "EntityScript.h"

class Entity;

class EntityScriptInstance {
public:
    EntityScriptInstance(Entity *entity, EntityScript *script) {
        this->entity = entity;
        this->script = script;
    };

    void reInitialize();

    void onLoad();
    void onStart();
    void onUpdate(float delta);
    void onStop();
    void onUnload();
    void setName(std::string name);

private:
    bool initialized = false;
    Entity *entity;
    EntityScript *script = nullptr;
    MonoClass *monoClass = nullptr;
    MonoObject *instance = nullptr;
    MonoMethod *onLoadMethod = nullptr, *onStartMethod = nullptr, *onUpdateMethod = nullptr,
            *onStopMethod = nullptr, *onUnloadMethod = nullptr, *setNameMethod = nullptr;
};


