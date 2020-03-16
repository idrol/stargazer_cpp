//
// Created by Idrol on 21-04-2018.
//

#include "LevelScript.h"
#include "../ScriptingEngine.h"
#include "LevelScriptInstance.h"



void LevelScript::reInitialize() {
    if(instance != nullptr) {
        instance->reInitialize();
    }
}

LevelScriptInstance *LevelScript::createInstance(Level *level) {
    instance = new LevelScriptInstance(level, this);
    return instance;
}
