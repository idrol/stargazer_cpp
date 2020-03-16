//
// Created by Idrol on 21-04-2018.
//

#include "LevelScriptInstance.h"
#include "../ScriptingEngine.h"
#include "LevelScript.h"

#define INIT_GUARD if(!initialized) return;

void LevelScriptInstance::reInitialize() {
    monoClass = mono_class_from_name(ScriptingEngine::getInstance().getImage(), "stargazer.Engine", script->getClassName().c_str());


    instance = mono_object_new(ScriptingEngine::getInstance().getDomain(), monoClass);

    mono_runtime_object_init(instance);

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
    initialized = true;
    onLoad();
}


void LevelScriptInstance::onLoad() {
    INIT_GUARD;
    mono_runtime_invoke(onLoadMethod, instance, NULL, NULL);
}

void LevelScriptInstance::onStart() {
    INIT_GUARD;
    mono_runtime_invoke(onStartMethod, instance, NULL, NULL);
}

void LevelScriptInstance::onUpdate(float delta) {
    INIT_GUARD;
    void *args [1];
    args[0] = &delta;
    mono_runtime_invoke(onUpdateMethod, instance, args, NULL);
}

void LevelScriptInstance::onStop() {
    INIT_GUARD;
    mono_runtime_invoke(onStopMethod, instance, NULL, NULL);
}

void LevelScriptInstance::onUnload() {
    INIT_GUARD;
    mono_runtime_invoke(onUnloadMethod, instance, NULL, NULL);
}
