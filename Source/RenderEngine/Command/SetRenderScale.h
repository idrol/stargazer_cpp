#pragma once
#include "Command.h"
#include <GLM\vec2.hpp>

class SetRenderScale: public Command {
public:
	SetRenderScale(glm::vec2 renderScale);
	void execute() override;

private:
	glm::vec2 renderScale;
};