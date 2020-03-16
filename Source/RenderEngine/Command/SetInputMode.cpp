#include "SetInputMode.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../Window/WindowUtil.h"

void SetInputMode::execute() {
	glfwSetInputMode(WindowUtil::getWindow(), GLFW_CURSOR, inputMode);
	WindowUtil::mouseState = inputMode;
}