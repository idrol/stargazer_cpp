#include "SetMousePosition.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "../Window/WindowUtil.h"

SetMousePosition::SetMousePosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void SetMousePosition::execute() {
	WindowUtil::setMousePosition(x, y);
}