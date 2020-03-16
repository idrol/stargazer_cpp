#pragma once

#include <string>

class Project;

class ProjectManager {
public:
    bool hasActiveProject();
    void chooseProject();
    void update(float delta);
    void closeProject();

private:
    void finalizeGui();
    bool verifyNewProjectPath(std::string path);
    bool verifyOpenProjectPath(std::string path);
    void verifyStargazerFolder(std::string path);
    Project *createNewProject(std::string path, std::string name);
    Project *loadProject(std::string path);

    Project *project = nullptr;
};


