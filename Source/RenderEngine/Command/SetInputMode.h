#pragma once

#include "Command.h"

class SetInputMode: public Command {
public:
	SetInputMode(int inputMode) {
		this->inputMode = inputMode;
	};
	void execute() override;
private:
	int inputMode;
};