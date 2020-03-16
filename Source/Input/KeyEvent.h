#pragma once

class KeyEvent {
public:
    KeyEvent(int key, int scancode, int action, int mods) {
        this->key = key;
        this->scancode = scancode;
        this->action = action;
        this->mods = mods;
    };

    int key, scancode, action, mods;
};
