#pragma once
#include "../Input/InputCallback.h"

class ImguiKeyCallback: public InputCallback {
public:
	ImguiKeyCallback(): InputCallback(ALL) {};
	void invoke(int key, int scancode, int action, int mods) override;
};