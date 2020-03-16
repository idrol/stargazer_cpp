#pragma once

#include <map>
#include <queue>
#include <GLM/glm.hpp>

class InputCallback;
class CharCallback;
class KeyEvent;
class ScrollCallback;
class MouseButtonEvent;
class MouseScrollEvent;

class InputHandler {
public:
    static void init();
    static void update();
    static void setKeyState(int key, int action);
    static int getKeyState(int key);
    static void setMouseState(int mouseButton, int action);
    static int getMouseState(int mouseButton);
    static void addKeyCallback(InputCallback *inputCallback);
    static void addMouseButtonCallback(InputCallback *inputCallback);
    static void addCharCallback(CharCallback *charCallback);
	static void setScrollCallback(ScrollCallback *scrollcallback);
    static glm::vec2 getMousePosition();
    static glm::vec2 getMouseDelta();

    static std::map<int, int> keyStates;
    static std::queue<KeyEvent*> keyBuffer;

    static std::map<int, int> mouseButtonStates;
    static std::queue<MouseButtonEvent*> mouseButtonBuffer;

	static std::queue<unsigned int> charBuffer;
	static std::queue<MouseScrollEvent*> scrollBuffer;

	static int mouseState;


private:
    static std::map<int, InputCallback*> keyCallBacks;

    static std::map<int, InputCallback*> mouseButtonCallbacks;
	static ScrollCallback *scrollCallback;
	static CharCallback *charCallback;

    static float mouseX, mouseY;
    static float dx, dy;
};
