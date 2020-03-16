#pragma once

#include <vector>
#include <string>
#include <map>
#include <boost/thread.hpp>

class Texture;
class Model;


enum Location{
    ENGINE, PROJECT, ALL
};

class ResourceManager {
public:
    static ResourceManager &getInstance() {
        static ResourceManager instance;
        return instance;
    };
    void registerLocation(std::string location, Location locationType = ALL);
    std::map<std::string, std::string> getFoldersAndFiles(std::string location, Location locationType = PROJECT);
    Texture *loadTexture(std::string path, Location locationType = ALL);
    Model *loadModel(std::string path, Location locationType = ALL);
    std::string resolvePath(std::string localPath, Location locationType = ALL, bool file = true);
    std::string toSystemPath(std::string localPath);
    std::string getProjectPath(std::string localPath);
    bool systemFileExists(std::string file);
    bool projectFileExists(std::string file);

private:
    ResourceManager() {
        // Register Engine assets
        registerLocation("Assets\\");
    };
    ~ResourceManager() = default;
    std::vector<std::string> pathPrefixes;
    std::vector<boost::thread> taskHandles;
    std::string enginePath;
    std::string projectPath;
};
