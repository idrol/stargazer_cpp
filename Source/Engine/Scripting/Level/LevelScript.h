#pragma once

#include "../Script.h"

class Level;
class LevelScriptInstance;

class LevelScript: public Script {
public:
    LevelScript(std::string scriptFile): Script("Level", scriptFile) {

    }

    LevelScript(std::string scriptFile, std::string systemScriptFile): Script("Level", scriptFile, systemScriptFile) {

    }

    void reInitialize() override;
    LevelScriptInstance *createInstance(Level *level);



private:
    LevelScriptInstance *instance = nullptr;
};
