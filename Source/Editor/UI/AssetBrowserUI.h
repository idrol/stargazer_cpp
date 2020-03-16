#pragma once

#include <string>
#include <vector>

class EditorUI;

class AssetBrowserUI {
public:
    AssetBrowserUI(EditorUI *editorUI) {
        this->editorUI = editorUI;
    };
    void renderUI();
    std::string getPath();

private:
    void renderPathButtons();
    void renderFoldersAndFiles();
    bool isTexture(std::string path);
    bool isHDRTexture(std::string path);

    EditorUI *editorUI;
    std::vector<std::string> cwd;
};


