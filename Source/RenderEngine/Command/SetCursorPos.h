#pragma once

#include "Command.h"

class SetCursorPos: public Command {
public:
	SetCursorPos(int x, int y) {
		this->x = x;
		this->y = y;
	};
	void execute() override;
private:
	int x;
	int y;
};