#include "SetCursorPos.h"
#include "../Window/WindowUtil.h"

void SetCursorPos::execute() {
	glfwSetCursorPos(WindowUtil::getWindow(), x, y);
}