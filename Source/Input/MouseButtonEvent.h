#pragma once

class MouseButtonEvent {
public:
    MouseButtonEvent(int button, int action, int mods) {
        this->button = button;
        this->action = action;
        this->mods = mods;
    }

    int button, action, mods;
};
