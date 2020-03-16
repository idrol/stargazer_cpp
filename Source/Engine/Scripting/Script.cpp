#include "Script.h"
#include "../../ResourceManager/ResourceManager.h"
#include "ScriptingEngine.h"

Script::Script(std::string className, std::string localScriptFile): Script(className, localScriptFile, ResourceManager::getInstance().resolvePath(localScriptFile))  {}

Script::Script(std::string className, std::string localScriptFile, std::string systemScriptFile) {
    this->className = className;
    this->localScriptFile = localScriptFile;
    this->systemScriptFile = systemScriptFile;
}

void Script::reInitialize() {
}

void Script::cleanupMono() {

}
