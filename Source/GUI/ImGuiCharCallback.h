#pragma once
#include "../Input/CharCallback.h"

class ImGuiCharCallback: public CharCallback {
public:
	void invoke(unsigned int codepoint) override;
};