#include "SetRenderScale.h"
#include "../RenderEngine.h"

SetRenderScale::SetRenderScale(glm::vec2 renderScale) {
	this->renderScale = renderScale;
}

void SetRenderScale::execute() {
	RenderEngine::getInstance().setRenderScale(renderScale);
}