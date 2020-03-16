#include "ResourceManager.h"
#include "../RenderEngine/Texture/TextureManager.h"
#include "../RenderEngine/Texture/Texture.h"
#include "../RenderEngine/Model/Model.h"
#include <boost/filesystem.hpp>
#include <GL/glew.h>
#include "LoadTextureTask.h"
#include "LoadModelTask.h"

using namespace boost::filesystem;

std::string ResourceManager::resolvePath(std::string localPath, Location locationType, bool file) {
    std::string systemPath = toSystemPath(localPath);
    std::string finalPath;
    if(locationType == ALL) {
        for(auto & prefix: pathPrefixes) {
            std::string testPath = prefix + systemPath;
            if(exists(testPath)) {
                if(file && is_regular_file(testPath)) {
                    return testPath;
                } else if(is_directory(testPath)) {
                    return testPath;
                }
            }
        }
    } else if(locationType == ENGINE) {
        std::string testPath = enginePath + systemPath;
        if(exists(testPath)) {
            if(file && is_regular_file(testPath)) {
                return testPath;
            } else if(is_directory(testPath)) {
                return testPath;
            }
        }
    } else if(locationType == PROJECT) {
        std::string testPath = projectPath + systemPath;
        if(exists(testPath)) {
            if(file && is_regular_file(testPath)) {
                return testPath;
            } else if(is_directory(testPath)) {
                return testPath;
            }
        }
    }

    return "";
}

std::string ResourceManager::toSystemPath(std::string localPath) {
    std::replace(localPath.begin(), localPath.end(), '/', '\\');
    return localPath;
}

void ResourceManager::registerLocation(std::string location, Location locationType) {
    if(locationType == ENGINE) {
        enginePath = location;
    } else if(locationType == PROJECT) {
        projectPath = location;
    }
    pathPrefixes.push_back(location);
}

Texture *ResourceManager::loadTexture(std::string path, Location locationType) {
    // Create new texture with the no_texture handle
    std::string finalPath = resolvePath(path, locationType);
    Texture *newTexture = new Texture(GL_RGBA, TextureManager::getTextureWithPath("Engine/textures/no_texture.png")->getTextureID(), path);
    TextureManager::registerTextureWithPath(path, newTexture);
    LoadTextureTask *loadTextureTask = new LoadTextureTask(newTexture, finalPath);
    taskHandles.push_back(boost::thread(boost::bind(&LoadTextureTask::loadResource, loadTextureTask)));
    return newTexture;
}

Model *ResourceManager::loadModel(std::string path, Location locationType) {
    std::string finalPath = resolvePath(path, locationType);
    Model *model = new Model();
    LoadModelTask *loadModelTask = new LoadModelTask(model, finalPath, path);
    taskHandles.push_back(boost::thread(boost::bind(&LoadModelTask::loadResource, loadModelTask)));
    return model;
}

std::map<std::string, std::string> ResourceManager::getFoldersAndFiles(std::string location, Location locationType) {
    std::string path;
    std::string systemPath = toSystemPath(location);
    if(locationType == PROJECT) {
        path = projectPath + systemPath;
    }

    boost::filesystem::path p (path);
    std::map<std::string, std::string> items;

    directory_iterator end_itr;
    for(directory_iterator itr(p); itr != end_itr; ++itr) {
        if(is_regular_file(itr->path()) || is_directory(itr->path())) {
            items[location + itr->path().filename().string()] = itr->path().filename().string();
        }
    }

    return items;
}

std::string ResourceManager::getProjectPath(std::string localPath) {
    std::string systemPath = toSystemPath(localPath);
    return projectPath + systemPath;
}

bool ResourceManager::systemFileExists(std::string file) {
    return exists(file) && is_regular_file(file);
}

bool ResourceManager::projectFileExists(std::string file) {
    std::string systemPath = getProjectPath(file);
    return systemFileExists(systemPath);
}
