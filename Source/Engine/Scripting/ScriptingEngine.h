#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <string>
#include <vector>
#include <map>

class Script;

class ScriptingEngine {
public:
    ScriptingEngine() {};
    // Singleton
    static ScriptingEngine &getInstance() {
        static ScriptingEngine instance;
        return instance;
    }
    ScriptingEngine(ScriptingEngine const&) = delete;
    void operator=(ScriptingEngine const&) = delete;

    void initialize();
    void createStargazerLibrary();
    void shutdownEngine();
    void registerScript(Script *script);
    bool compileScripts();
    void update();
    Script *getScript(std::string name);
    MonoImage *getImage();
    MonoDomain *getDomain();

private:
    int dll_count = 1;
    std::map<std::string, Script*> scripts;
    MonoDomain *rootDomain = nullptr, *executionDomain = nullptr;
    MonoAssembly *assembly = nullptr;
    MonoImage *image = nullptr;
    std::string dllPath;
    std::string dllPrefix;
    bool initialized = false;
};
