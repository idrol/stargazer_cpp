#include "Project.h"
#include <iostream>
#include <fstream>
#include <json.hpp>
#include "../../Engine/Entity/EntityManager.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/StargazerEngine.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../EditorLevel.h"
#include <boost/filesystem.hpp>
#include "../../Engine/Scripting/ScriptingEngine.h"

void Project::createProjectInformation() {
    std::ofstream projectFile;
    projectFile.open(path + "\\Project.project");
    nlohmann::json j2 = {
            {"name", "Project"},
            {"defaultLevel", "Levels/Default.level"},
    };
    projectFile << j2.dump();
    projectFile.close();
}

void Project::createProject() {
    createProjectInformation();
    createDefaultLevel();
}

void Project::loadProjectInformation() {
    std::ifstream projectFile;
    projectFile.open(path + "\\Project.project");
    std::string data((std::istreambuf_iterator<char>(projectFile)),
                     (std::istreambuf_iterator<char>()));
    projectFile.close();
    nlohmann::json projectJson = nlohmann::json::parse(data);
    name = projectJson["name"];
    std::string defaultLevel = projectJson["defaultLevel"];
    defaultLevelPath = getPath() + "\\" + defaultLevel;
}

void Project::loadDefaultLevel() {
    std::ifstream levelFile;
    levelFile.open(defaultLevelPath);
    std::string data((std::istreambuf_iterator<char>(levelFile)),
                     (std::istreambuf_iterator<char>()));
    levelFile.close();
    nlohmann::json levelJson = nlohmann::json::parse(data);
    level = new EditorLevel(this, levelJson["name"], defaultLevelPath);
    StargazerEngine::getInstance().switchLevel(level);
}

void Project::createDefaultLevel() {
    std::ofstream levelFile;
    if(!boost::filesystem::exists(path + "\\Levels")) {
        boost::filesystem::create_directory(path + "\\Levels");
    }
    levelFile.open(path + "\\Levels\\Default.level");
    nlohmann::json j2 = {
            {"name", "defaultLevel"},
            {"script", "Scripts/Level.cs"},
            {"entites", {}}
    };
    levelFile << j2.dump();
    levelFile.close();
    createDefaultLevelScript();
    defaultLevelPath = getPath() + "\\Levels\\Default.level";
    level = new EditorLevel(this, "defaultLevel", getPath() + "\\Levels\\Default.level");
    StargazerEngine::getInstance().switchLevel(level);
}


void Project::createDefaultLevelScript() {
    if(!boost::filesystem::exists(path + "\\Scripts")) {
        boost::filesystem::create_directory(path + "\\Scripts");
    }
    std::string defaultLevelScript = ResourceManager::getInstance().resolvePath("Engine/Script/Level.cs", ENGINE);
    std::string levelScript = ResourceManager::getInstance().getProjectPath("Scripts/Level.cs");
    boost::filesystem::copy(defaultLevelScript, levelScript);
}


void Project::loadProject() {
    loadProjectInformation();
    loadDefaultLevel();
    ScriptingEngine::getInstance().initialize();
}

void Project::update(float delta) {
    level->update(delta);
}

void Project::close() {
    if(level != nullptr) {
        if(level->isPlaying()) {
            level->stop();
        }
        level->unload();
    }
}

Project::Project(std::string path) {
    this->path = path;
    ResourceManager::getInstance().registerLocation(path + "\\", PROJECT);
}


