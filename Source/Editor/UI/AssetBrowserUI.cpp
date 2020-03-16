#include "AssetBrowserUI.h"
#include "../../GUI/imgui.h"
#include "../../GUI/addons/imguidock/imguidock.h"
#include "../../ResourceManager/ResourceManager.h"
#include <boost/filesystem.hpp>

void AssetBrowserUI::renderUI() {
    if(ImGui::BeginDock("Asset Browser")) {
        renderPathButtons();

        renderFoldersAndFiles();
    }

    ImGui::EndDock();
}

void AssetBrowserUI::renderFoldersAndFiles() {
    std::map<std::string, std::string> foldersAndFiles = ResourceManager::getInstance().getFoldersAndFiles(getPath());
    float windowWidth = ImGui::GetWindowWidth();
    float itemSize = 124;
    int columns = (int)(windowWidth / itemSize);
    if(columns < 1) columns = 1;
    ImGui::Columns(columns, NULL, false);

    for(auto & item: foldersAndFiles) {

        if(ImGui::Button(item.second.c_str(), ImVec2(itemSize, itemSize))) {
            if(boost::filesystem::is_directory(ResourceManager::getInstance().resolvePath(item.first, PROJECT, false))) {
                cwd.push_back(item.second);
            }
        }
        if(isTexture(item.first)) {
            if(ImGui::BeginDragDropSource()) {
                auto *pathToFile = new std::string(item.first);
                ImGui::SetDragDropPayload("texture", pathToFile, pathToFile->size());
                ImGui::Button(item.second.c_str(), ImVec2(itemSize, itemSize));
                ImGui::EndDragDropSource();
            }
        }
        if(isHDRTexture(item.first)) {
            if(ImGui::BeginDragDropSource()) {
                auto *pathToFile = new std::string(item.first);
                ImGui::SetDragDropPayload("HDR", pathToFile, pathToFile->size());
                ImGui::Button(item.second.c_str(), ImVec2(itemSize, itemSize));
                ImGui::EndDragDropSource();
            }
        }
        ImGui::NextColumn();
    }

    ImGui::Columns(1);
}


void AssetBrowserUI::renderPathButtons() {
    if(ImGui::Button("Project")) {
        cwd = std::vector<std::string>();
    }
    std::vector<std::string> cwdTmp;
    for(auto & cwdPart: cwd) {
        cwdTmp.push_back(cwdPart);
        ImGui::SameLine();
        if(ImGui::Button(cwdPart.c_str())) {
            cwd = cwdTmp;
            break;
        }
    }
}

std::string AssetBrowserUI::getPath() {
    std::string path;
    for(auto & pathPart: cwd) {
        path += pathPart + "/";
    }
    return path;
}

bool AssetBrowserUI::isTexture(std::string path) {
    boost::filesystem::path p(path);
    std::string extension = p.extension().string();
    return extension == ".png";
}

bool AssetBrowserUI::isHDRTexture(std::string path) {
    boost::filesystem::path p(path);
    std::string extension = p.extension().string();
    return extension == ".hdr";
}

