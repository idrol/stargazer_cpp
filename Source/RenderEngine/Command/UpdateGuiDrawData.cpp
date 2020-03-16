#include "UpdateGuiDrawData.h"
#include "../RenderEngine.h"

UpdateGuiDrawData::UpdateGuiDrawData(std::vector<DrawList*> drawList) {
	this->drawlist = drawList;
}

void UpdateGuiDrawData::execute() {
	RenderEngine::getInstance().setGuiDrawData(drawlist);
}