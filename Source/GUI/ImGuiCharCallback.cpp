#include "ImGuiCharCallback.h"
#include "imgui.h"

void ImGuiCharCallback::invoke(unsigned int codepoint) {
	ImGuiIO& io = ImGui::GetIO();
	if(codepoint > 0 && codepoint < 0x10000) {
		io.AddInputCharacter((unsigned short)codepoint);
	}
};