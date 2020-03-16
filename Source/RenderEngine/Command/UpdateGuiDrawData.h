#pragma once

#include "Command.h"
#include <vector>

struct DrawList;

class UpdateGuiDrawData: public Command {
public:
	UpdateGuiDrawData(std::vector<DrawList*> drawList);
	void execute() override;

private:
	std::vector<DrawList*> drawlist;
};