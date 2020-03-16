#pragma once

#include <vector>

struct DrawList;
struct GLFWwindow;

void ImGui_ImplStargazerRender_RenderDrawLists(std::vector<DrawList*> drawlist);

bool ImGui_ImplStargazerRender_Init(GLFWwindow *window, bool install_callbacks);
void ImGui_ImplStargazerRender_Shutdown();

bool ImGui_ImplStargazerRender_CreateFontsTexture();
bool ImGui_ImplStargazerRender_CreateDeviceObjects();
void ImGui_ImplStargazerRender_InvalidateDeviceObjects();