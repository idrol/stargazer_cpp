#pragma once

#include "Command.h"

class SetMousePosition: public Command {
public:
	SetMousePosition(float x, float y);
	void execute() override;

private:
	float x, y;
};