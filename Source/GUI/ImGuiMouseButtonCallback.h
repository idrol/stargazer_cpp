#pragma once
#include "../Input/InputCallback.h"

class ImGuiMouseButtonCallback: public InputCallback {
public:
	ImGuiMouseButtonCallback(bool (&mouseJustPressed)[3]): InputCallback(-1) {
		g_MouseJustPressed = &mouseJustPressed;
	};

	void invoke(int button, int action, int mods) override;
private:
	bool (*g_MouseJustPressed)[3];
};