#include "ImGuiScrollCallback.h"
#include "imgui.h"

void ImGuiScrollCallback::invoke(double xoffset, double yoffset) {
	ImGuiIO& io = ImGui::GetIO();
	// Not implemented yet in ImGui io.MouseWheelH += (float) xoffset;
	io.MouseWheel = (float) yoffset;
}