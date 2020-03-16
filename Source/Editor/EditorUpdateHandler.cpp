#include "EditorUpdateHandler.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/Command/RegisterShaderDefaults.h"
#include "../RenderEngine/Command/RegisterTextureDefaults.h"
#include <chrono>
#include "../Input/StargazerInput.h"
#include "UI\EditorUI.h"
#include "EditorLevel.h"
#include "../Engine/StargazerEngine.h"
#include "../ResourceManager/ResourceManager.h"
#include "Project/ProjectManager.h"
#include "../GUI/imgui.h"
#include "../GUI/imgui_impl_stargazer_update.h"
#include "../Engine/Scripting/ScriptingEngine.h"
#include <iostream>

EditorUpdateHandler::EditorUpdateHandler() {

}

void EditorUpdateHandler::run() {
	while(!RenderEngine::getInstance().initialized) {
		// Ensure renderengine is initialized
	};
	RenderEngine::getInstance().renderToTexture(true);
	initialize();
	float delta = 0;
	while (StargazerEngine::getInstance().running) {
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		this->loop(delta/1000);

		boost::this_thread::sleep_for(boost::chrono::milliseconds(16));
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> time_span = t2 - t1;
		delta = time_span.count();
	}
    std::cout << "Shutting down engine" << std::endl;
    projectManager->closeProject();
}

void EditorUpdateHandler::initialize() {
	RenderEngine::getInstance().addCommand(new RegisterShaderDefaults());
	RenderEngine::getInstance().addCommand(new RegisterTextureDefaults());
	RenderEngine::getInstance().createBRDFLUT("brdfLUT");
	RenderEngine::getInstance().cycleCommandBuffer();
    ImGui_ImplStargazerUpdate_InstallCallbacks();
	ScriptingEngine::getInstance().createStargazerLibrary();
    projectManager = new ProjectManager();
	ui = new EditorUI();
	ImGui::StyleColorsLight(&ImGui::GetStyle());
}

void EditorUpdateHandler::loop(float delta) {
	InputHandler::update();
    if(!projectManager->hasActiveProject()) {
        ImGui_ImplStargazerUpdate_NewFrame(delta, true);
        projectManager->chooseProject();
    } else {
        projectManager->update(delta);
        ui->update(delta);
    }
}

void EditorUpdateHandler::stop() {
	StargazerEngine::getInstance().running = false;
}