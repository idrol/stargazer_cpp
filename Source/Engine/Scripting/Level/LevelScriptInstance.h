//
// Created by Idrol on 21-04-2018.
//

#pragma once

#include <mono/metadata/object.h>
#include <mono/metadata/debug-helpers.h>

class Level;
class LevelScript;

class LevelScriptInstance {
public:
    LevelScriptInstance(Level *level, LevelScript *script) {
        this->level = level;
        this->script = script;
    };
    void reInitialize();

    void onLoad();
    void onStart();
    void onUpdate(float delta);
    void onStop();
    void onUnload();
    LevelScript *getScript() {
        return script;
    };

private:
    bool initialized = false;
    Level *level;
    LevelScript *script = nullptr;
    MonoClass *monoClass = nullptr;
    MonoObject *instance = nullptr;
    MonoMethod *onLoadMethod = nullptr, *onStartMethod = nullptr, *onUpdateMethod = nullptr,
            *onStopMethod = nullptr, *onUnloadMethod = nullptr;
};


