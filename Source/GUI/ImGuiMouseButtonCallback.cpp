#include "ImGuiMouseButtonCallback.h"
#include <GL\glew.h> 
#include <GLFW\glfw3.h>
#include <iostream>

void ImGuiMouseButtonCallback::invoke(int button, int action, int mods) {
	if(action == GLFW_PRESS && button >= 0 && button < 3) {
		*g_MouseJustPressed[button] = true;
	}
}