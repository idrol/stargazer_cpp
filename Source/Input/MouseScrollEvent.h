#pragma once

class MouseScrollEvent {
public:
	MouseScrollEvent(double xoffset, double yoffset) {
		this->xoffset = xoffset;
		this->yoffset = yoffset;
	};
	double xoffset, yoffset;
};