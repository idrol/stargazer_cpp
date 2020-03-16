#include "ScriptingEngine.h"
#include <stdlib.h>
#include "../../ResourceManager/ResourceManager.h"
#include "Script.h"
#include <iostream>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/mono-gc.h>
#include "Level/LevelScript.h"
#include "Entity/EntityScript.h"

void ScriptingEngine::initialize() {
    if(!ResourceManager::getInstance().systemFileExists(dllPath)) {
        return;
    }
    if(rootDomain == nullptr) {
        rootDomain = mono_jit_init("stargazer_engine");
    }

    executionDomain = mono_domain_create_appdomain("Execution Domain", NULL);
    mono_domain_set(executionDomain, false);


    assembly = mono_domain_assembly_open(executionDomain, dllPath.c_str());

    if(!assembly) {
        std::cout << "Mono assembly failed" << std::endl;
        return;
    }
    image = mono_assembly_get_image(assembly);

    initialized = true;

    for(auto & script: scripts) {
        script.second->reInitialize();
    }

}

void ScriptingEngine::shutdownEngine() {
    if(initialized) {
        mono_domain_set(rootDomain, false);
        mono_domain_unload(executionDomain);
        mono_gc_collect (mono_gc_max_generation ());
    }
}

bool ScriptingEngine::compileScripts() {
    shutdownEngine();
    std::string scriptPath = ResourceManager::getInstance().resolvePath("Scripts/Level.cs");
    dllPath = ResourceManager::getInstance().getProjectPath("scripts.dll");
    //dllPath.append(std::to_string(dll_count++));
    //dllPath.append(".dll");
    std::string command;
    command.append("mcs /unsafe /target:library /out:\"");
    command.append(dllPath);
    command.append("\"");
    for(auto & script: scripts) {
        command.append(" \"");
        command.append(script.second->getSystemScriptPath());
        command.append("\"");
    }
    std::cout << "Compile command is " << command << std::endl;
    int i = system(command.c_str());
    if(i != 0) {
        std::cout << "Compile command returned " << i << std::endl;
        return false;
    }
    initialize();
    return true;
}

void ScriptingEngine::update() {
    /*
    MonoClass *monoClass = mono_class_from_name(image, "", "Level");
    MonoMethodDesc *monoMethodDesc = mono_method_desc_new("Level:onUpdate()", false);

    MonoMethod *monoMethod = mono_method_desc_search_in_class(monoMethodDesc, monoClass);
    void *args[0];
    mono_runtime_invoke(monoMethod, NULL, args, NULL);
     */
}

void ScriptingEngine::registerScript(Script *script) {
    scripts[script->getClassName()] = script;
}

MonoImage *ScriptingEngine::getImage() {
    return image;
}

MonoDomain *ScriptingEngine::getDomain() {
    return executionDomain;
}

void ScriptingEngine::createStargazerLibrary() {
    registerScript(new EntityScript("Engine/Script/Entity.cs"));
    registerScript(new Script("EntityBase", "Engine/Script/Base/EntityBase.cs"));
    registerScript(new Script("Component", "Engine/Script/Component.cs"));
}

Script *ScriptingEngine::getScript(std::string name) {
    auto it = scripts.find(name);
    if(it != scripts.end()) {
        return it->second;
    }
    return nullptr;
}
