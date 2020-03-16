#pragma once
#include "../Input/ScrollCallback.h"

class ImGuiScrollCallback: public ScrollCallback {
public:
	void invoke(double xoffset, double yoffset) override;
};