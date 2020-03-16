//
// Created by Idrol on 21-04-2018.
//

#include "EntityScriptInstance.h"
#include "../ScriptingEngine.h"
#include "../../Entity/Entity.h"

#define INIT_GUARD if(!initialized) return;

void EntityScriptInstance::reInitialize() {
    MonoImage *image = ScriptingEngine::getInstance().getImage();
    const char *name = script->getClassName().c_str();
    monoClass = mono_class_from_name(image, "stargazer.Engine", name);

    instance = mono_object_new(ScriptingEngine::getInstance().getDomain(), monoClass);
    void *args [1];
    std::cout << "Creating Entity base from c++ with c entity pointer " << reinterpret_cast<uintptr_t>(entity) << std::endl;
    uintptr_t ptr = reinterpret_cast<uintptr_t>(entity);
    uintptr_t *ptr2 = &ptr;
    args[0] = ptr2;

    MonoMethodDesc *ctorDesc = mono_method_desc_new("*:.ctor(uintptr)", false);
    MonoMethod *ctorMethod = mono_method_desc_search_in_class(ctorDesc, monoClass);

    mono_runtime_invoke(ctorMethod, instance, args, NULL);
    mono_method_desc_free(ctorDesc);

    MonoMethodDesc *onLoadDesc = mono_method_desc_new("*:onLoad()", false);
    onLoadMethod = mono_method_desc_search_in_class(onLoadDesc, monoClass);
    mono_method_desc_free(onLoadDesc);

    MonoMethodDesc *onStartDesc = mono_method_desc_new("*:onStart()", false);
    onStartMethod = mono_method_desc_search_in_class(onStartDesc, monoClass);
    mono_method_desc_free(onStartDesc);

    MonoMethodDesc *onUpdateDesc = mono_method_desc_new("*:onUpdate(single)", false);
    onUpdateMethod = mono_method_desc_search_in_class(onUpdateDesc, monoClass);
    mono_method_desc_free(onUpdateDesc);

    MonoMethodDesc *onStopDesc = mono_method_desc_new("*:onStop()", false);
    onStopMethod = mono_method_desc_search_in_class(onStopDesc, monoClass);
    mono_method_desc_free(onStopDesc);

    MonoMethodDesc *onUnloadDesc = mono_method_desc_new("*:onUnload()", false);
    onUnloadMethod = mono_method_desc_search_in_class(onUnloadDesc, monoClass);
    mono_method_desc_free(onUnloadDesc);

    MonoMethodDesc *setNameDesc = mono_method_desc_new("*:setName(string)", false);
    setNameMethod = mono_method_desc_search_in_class(setNameDesc, monoClass);
    mono_method_desc_free(setNameDesc);
    initialized = true;
    onLoad();
}

void EntityScriptInstance::onLoad() {
    INIT_GUARD;
    mono_runtime_invoke(onLoadMethod, instance, NULL, NULL);
}

void EntityScriptInstance::onStart() {
    INIT_GUARD;
    mono_runtime_invoke(onStartMethod, instance, NULL, NULL);
}

void EntityScriptInstance::onUpdate(float delta) {
    INIT_GUARD;
    void *args[1];
    args[0] = &delta;
    mono_runtime_invoke(onUpdateMethod, instance, args, NULL);
}

void EntityScriptInstance::onStop() {
    INIT_GUARD;
    mono_runtime_invoke(onStopMethod, instance, NULL, NULL);
}

void EntityScriptInstance::onUnload() {
    INIT_GUARD;
    mono_runtime_invoke(onUnloadMethod, instance, NULL, NULL);
}

void EntityScriptInstance::setName(std::string name) {
    INIT_GUARD;
    void *args[1];
    args[0] = mono_string_new(ScriptingEngine::getInstance().getDomain(), name.c_str());
    mono_runtime_invoke(setNameMethod, instance, args, NULL);
}
