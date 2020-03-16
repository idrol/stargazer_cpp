#pragma once

#include <string>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/object.h>

#define init_guard if(!initialized) return;

class Script {
public:
    Script(std::string className, std::string localScriptFile);
    Script(std::string className, std::string localScriptFile, std::string systemScriptFile);

    virtual void reInitialize();
    std::string getClassName() {
        return className;
    };
    std::string getLocalScriptPath() {
        return localScriptFile;
    };
    std::string getSystemScriptPath() {
        return systemScriptFile;
    };
    virtual void cleanupMono();

protected:
    std::string className, localScriptFile, systemScriptFile;
    bool initialized = false;
};


