#include "imgui_impl_stargazer_update.h"
#include "imgui.h"
#include "../RenderEngine/Window/WindowUtil.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/Command/SetInputMode.h"
#include "../RenderEngine/Command/SetMousePosition.h"
#include "../Input/InputHandler.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "ImguiKeyCallback.h"
#include "ImGuiScrollCallback.h"
#include "ImGuiCharCallback.h"
#include "ImGuiMouseButtonCallback.h"
#include <iostream>

static bool g_MouseJustPressed[3] = { false, false, false };

void ImGui_ImplStargazerUpdate_NewFrame(float delta, bool changeCursorState) {

	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	int w, h;
	int display_w, display_h;
	glm::vec2 windowSize = WindowUtil::getWindowSize();
	glm::vec2 frambufferSize = WindowUtil::getFrameBufferSize();
	w = windowSize.x;
	h = windowSize.y;
	display_w = frambufferSize.x;
	display_h = frambufferSize.y;
	io.DisplaySize = ImVec2((float)w, (float)h);
	io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

	// Setup time step
	//double current_time =  glfwGetTime();
	//io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f/60.0f);
	io.DeltaTime = delta;
	//g_Time = current_time; // Timer not reliable from main thread

	// Setup inputs
	// (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
	if (WindowUtil::getWindowFocused()) // Main thread
	{
		if (io.WantMoveMouse)
		{
			RenderEngine::getInstance().addCommand(new SetMousePosition(io.MousePos.x, io.MousePos.y));
		}
		else
		{
			glm::vec2 mousePos = InputHandler::getMousePosition();
			io.MousePos = ImVec2(mousePos.x, mousePos.y);
		}
	}
	else
	{
		io.MousePos = ImVec2(-FLT_MAX,-FLT_MAX);
	}

	for (int i = 0; i < 3; i++)
	{
		// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
		io.MouseDown[i] = g_MouseJustPressed[i] || InputHandler::getMouseState(i) != 0;
		g_MouseJustPressed[i] = false;
	}

	// Hide OS mouse cursor if ImGui is drawing i
	if(changeCursorState) RenderEngine::getInstance().addCommand(new SetInputMode(io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL));

	// Start the frame. This call will update the io.WantCaptureMouse, io.WantCaptureKeyboard flag that you can use to dispatch inputs (or not) to your application.
	ImGui::NewFrame();
}

void ImGui_ImplStargazerUpdate_InstallCallbacks() {
	InputHandler::addKeyCallback(new ImguiKeyCallback());
	InputHandler::setScrollCallback(new ImGuiScrollCallback());
	InputHandler::addMouseButtonCallback(new ImGuiMouseButtonCallback(g_MouseJustPressed));
	InputHandler::addCharCallback(new ImGuiCharCallback());
}