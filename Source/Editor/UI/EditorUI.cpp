#include "EditorUI.h"
#include "../../GUI/imgui.h"
#include "../../GUI/imgui_impl_stargazer_update.h"
#include "../../GUI/addons/imguihelper/imguihelper.h"
#include "../../GUI/addons/imguidock/imguidock.h"
#include "../../RenderEngine/RenderEngine.h"
#include "../../RenderEngine/Command/UpdateGuiDrawData.h"
#include "../../RenderEngine/Command/SetInputMode.h"
#include "../../RenderEngine/Command/SetRenderScale.h"
#include "../../RenderEngine/Window/WindowUtil.h"
#include "LevelUI.h"
#include "InspectorUI.h"
#include "PrimitivesUI.h"
#include "AssetBrowserUI.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include "../../GUI/addons/imguifilesystem/imguifilesystem.h"
#include "../../Engine/StargazerEngine.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Scripting/ScriptingEngine.h"

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec2 editor_size = ImVec2(0,0);

EditorUI::EditorUI() {
	levelUI = new LevelUI(this);
	inspectorUI = new InspectorUI(this);
	primitivesUI = new PrimitivesUI(this);
	assetBrowserUI = new AssetBrowserUI(this);
}

void EditorUI::update(float delta)  {
	if(!RenderEngine::getInstance().imguiDevicesValid) return;
	prepareGui(delta);
	renderGui();
	finalizeGui();
}

void EditorUI::prepareGui(float delta) {
	ImGui_ImplStargazerUpdate_NewFrame(delta, !isEditorWindowFocused);
}

void EditorUI::renderGui() {
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	const ImGuiWindowFlags flags =  (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);
	const float oldWindowRounding = ImGui::GetStyle().WindowRounding;ImGui::GetStyle().WindowRounding = 0;
	const bool visible = ImGui::Begin("imguidock window (= lumix engine's dock system)",NULL,ImVec2(0, 0),1.0f,flags);
    ImGui::GetStyle().WindowRounding = oldWindowRounding;

	static bool play = false;

	if(ImGui::BeginMenuBar()) {
        if(ImGui::BeginMenu("Controlls")) {
            if(ImGui::MenuItem("Play Level", NULL, &play)) {
                if(play) {
                    StargazerEngine::getInstance().getActiveLevel()->start();
                } else {
                    StargazerEngine::getInstance().getActiveLevel()->stop();
                }
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Scripts")) {
        	if(ImGui::MenuItem("Compile")) {
				ScriptingEngine::getInstance().compileScripts();
        	}
			ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

	if (visible) {
		ImGui::BeginDockspace();

		ImGui::SetNextDock(ImGuiDockSlot_Bottom);
		assetBrowserUI->renderUI();

		ImGui::SetNextDock(ImGuiDockSlot_Top);
		primitivesUI->renderUI();

		ImGui::SetNextDock(ImGuiDockSlot_Right);

		if(ImGui::BeginDock("Editor", nullptr, 0, ImVec2(0, 0))) {
			ImVec2 size = ImGui::GetWindowSize();
			size.y -= 16;
			if(editor_size.x != size.x || editor_size.y != size.y) {
				RenderEngine::getInstance().addCommand(new SetRenderScale(glm::vec2(size.x, size.y)));
			}
			editor_size = size;
			if(ImGui::RenderEngine((void*)(RenderEngine::getInstance().getPostProcessorTexture()), size)){
				isEditorWindowFocused = true;
				if(WindowUtil::getMouseMode() == GLFW_CURSOR_NORMAL ||WindowUtil::getMouseMode() == GLFW_CURSOR_HIDDEN) {
					RenderEngine::getInstance().addCommand(new SetInputMode(GLFW_CURSOR_DISABLED));
				}
			} else if(isEditorWindowFocused) {
				isEditorWindowFocused = false;
				if(WindowUtil::getMouseMode() != GLFW_CURSOR_NORMAL) {
					RenderEngine::getInstance().addCommand(new SetInputMode(GLFW_CURSOR_NORMAL));
				}
			}
		}
		ImGui::EndDock();

		
		ImGui::SetNextDock(ImGuiDockSlot_Right);
		levelUI->renderUI();


		ImGui::SetNextDock(ImGuiDockSlot_Bottom);
		inspectorUI->renderUI();

		ImGui::EndDockspace();
	}
	ImGui::End();

	//ImGui::ShowDemoWindow();
}

void EditorUI::finalizeGui() {
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

LevelUI *EditorUI::getLevelUI() {
	return levelUI;
}

InspectorUI *EditorUI::getInspectorUI() {
	return inspectorUI;
}

PrimitivesUI *EditorUI::getPrimitivesUI() {
	return primitivesUI;
}

AssetBrowserUI *EditorUI::getAssetBrowserUI() {
	return assetBrowserUI;
}
