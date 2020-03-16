#include "ImguiKeyCallback.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "imgui.h"

void ImguiKeyCallback::invoke(int key, int scancode, int action, int mods) {
	ImGuiIO& io = ImGui::GetIO();
	if(action == GLFW_PRESS) {
		io.KeysDown[key] = true;
	}
	if(action == GLFW_RELEASE) {
		io.KeysDown[key] = false;
	}

	(void)mods;
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
}