#include "ProjectManager.h"
#include "../../GUI/imgui.h"
#include "../../GUI/addons/imguifilesystem/imguifilesystem.h"
#include <vector>
#include "../../RenderEngine/RenderEngine.h"
#include "../../RenderEngine/Command/UpdateGuiDrawData.h"
#include <boost/filesystem.hpp>
#include "Project.h"
#include "../EditorLevel.h"
#include "../../Engine/StargazerEngine.h"
#include <Shlobj.h>

void ProjectManager::chooseProject() {
    ImGui::Begin("File Chooser");

    static bool chooseProjectName = false;
    static std::string path;
    std::string my_documents;
    WCHAR docPath[MAX_PATH + 1];
    if(SHGetSpecialFolderPathW(HWND_DESKTOP, docPath, CSIDL_MYDOCUMENTS, FALSE)) {
        std::wstring ws(docPath);
        my_documents = std::string(ws.begin(), ws.end());
    }
    my_documents = my_documents + "\\Stargazer";

    verifyStargazerFolder(my_documents);

    if(!chooseProjectName) {
        const bool createNew = ImGui::Button("Create new project");
        static  ImGuiFs::Dialog newDLG;

        const char* newPath = newDLG.chooseFolderDialog(createNew, my_documents.c_str());

        if (strlen(newPath)>0) {
            // A path (chosenPath) has been chosen RIGHT NOW. However we can retrieve it later more comfortably using: dlg.getChosenPath()
        }
        ImGui::SameLine();

        const bool openProject = ImGui::Button("Open project");
        static ImGuiFs::Dialog openDlg;
        const char* openPath = openDlg.chooseFolderDialog(openProject, my_documents.c_str());

        if(strlen(openPath)>0) {

        }

        if (strlen(newDLG.getChosenPath())>0) {
            std::string s(newDLG.getChosenPath());
            if(verifyNewProjectPath(s)) {
                path = s;
                chooseProjectName = true;
                ImGui::OpenPopup("Project Name");
            } else {
                ImGui::Text("Folder is not empty");
            }
        }
        if(strlen(openDlg.getChosenPath())>0) {
            std::string s(openDlg.getChosenPath());
            if(verifyOpenProjectPath(s)) {
                project = loadProject(s);
            } else {
                ImGui::Text("Given path does not contain a valid project.");
            }
            ImGui::Text("Open project at: \"%s\"", openDlg.getChosenPath());
        }
    } else if(chooseProjectName) {
        if (ImGui::BeginPopupModal("Project Name", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Choose a name for you project.");
            ImGui::Separator();
            static char name[128] = "My Project";
            ImGui::InputText("Name", name, IM_ARRAYSIZE(name));
            if(ImGui::Button("Done")) {
                project = createNewProject(path, std::string(name));
                ImGui::CloseCurrentPopup();
            }
			ImGui::EndPopup();
        }
    }

    ImGui::End();

    finalizeGui();
}


bool ProjectManager::verifyOpenProjectPath(std::string path) {
    if(boost::filesystem::is_directory(path)) {
        if(boost::filesystem::exists(path + "\\Project.project")) {
            return true;
        }
    }
    return false;
}

bool ProjectManager::verifyNewProjectPath(std::string path) {
    if(boost::filesystem::is_directory(path)) {
        if(boost::filesystem::is_empty(path)) {
            return true;
        }
    }
    return false;
}

Project *ProjectManager::createNewProject(std::string path, std::string name) {
    Project *project = new Project(path, name);
    project->createProject();
    return project;
}

Project *ProjectManager::loadProject(std::string path) {
    Project *project = new Project(path);
    project->loadProject();
    return project;
}

void ProjectManager::finalizeGui() {
    ImGui::Render();
    ImDrawData *drawData = ImGui::GetDrawData();
    std::vector<DrawList*> drawLists;
    for(int i = 0; i < drawData->CmdListsCount; i++) {
        DrawList *drawList = new DrawList();

        for(ImDrawCmd command: drawData->CmdLists[i]->CmdBuffer) {
            drawList->drawCmd.push_back(ImDrawCmd(command));
        }

        for(ImDrawIdx drawIndex: drawData->CmdLists[i]->IdxBuffer) {
            drawList->drawIndex.push_back(ImDrawIdx(drawIndex));
        }

        for(ImDrawVert drawVert: drawData->CmdLists[i]->VtxBuffer) {
            drawList->drawVert.push_back(ImDrawVert(drawVert));
        }
        drawLists.push_back(drawList);
    }

    RenderEngine::getInstance().addCommand(new UpdateGuiDrawData(drawLists));
}

bool ProjectManager::hasActiveProject() {
    return project != nullptr;
}

void ProjectManager::update(float delta) {
    project->update(delta);
}

void ProjectManager::closeProject() {
    if(project != nullptr) project->close();
}

void ProjectManager::verifyStargazerFolder(std::string path) {
    if(!boost::filesystem::exists(path)) {
        boost::filesystem::create_directory(path);
    }
}




