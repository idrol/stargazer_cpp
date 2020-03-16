#pragma once

#include <string>

class EditorLevel;

class Project {
public:
    Project(std::string path, std::string name): Project(path){
        this->name = name;
    };
    Project(std::string path);
    void createProject();
    void loadProject();
    void update(float delta);
    void close();
    std::string getPath() {
        return path;
    }

private:
    void createProjectInformation();
    void createDefaultLevel();
    void createDefaultLevelScript();
    void loadProjectInformation();
    void loadDefaultLevel();
    std::string path, name, defaultLevelPath;
    EditorLevel *level = nullptr;
};


