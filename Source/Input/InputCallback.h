#pragma once

class InputCallback {
public:
    explicit InputCallback(int key) {this->key = key;};
    virtual void invoke(int action) {};
    virtual void invoke(int button, int action, int mods) {invoke(action);};
    virtual void invoke(int key, int scancode, int action, int mods) {invoke(action);};

    int key;
    static const int ALL = -1;
};
