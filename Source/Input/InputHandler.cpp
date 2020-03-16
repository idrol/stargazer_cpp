//
// Created by Idrol on 04-10-2017.
//

#include "InputHandler.h"
#include "../RenderEngine/Window/WindowUtil.h"
#include <GLFW\glfw3.h>
#include "KeyEvent.h"
#include "MouseButtonEvent.h"
#include "CharCallback.h"
#include "InputCallback.h"
#include "ScrollCallback.h"
#include "MouseScrollEvent.h"
#include <iostream>

std::map<int, InputCallback*> InputHandler::keyCallBacks;
std::map<int, int> InputHandler::keyStates;
std::queue<KeyEvent*> InputHandler::keyBuffer;

std::map<int, InputCallback*> InputHandler::mouseButtonCallbacks;
std::map<int, int> InputHandler::mouseButtonStates;
std::queue<MouseButtonEvent*> InputHandler::mouseButtonBuffer;

std::queue<unsigned int> InputHandler::charBuffer;
std::queue<MouseScrollEvent*> InputHandler::scrollBuffer;

float InputHandler::mouseX;
float InputHandler::mouseY;
float InputHandler::dx;
float InputHandler::dy;

int InputHandler::mouseState = GLFW_CURSOR_NORMAL;

CharCallback *InputHandler::charCallback;
ScrollCallback *InputHandler::scrollCallback;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputHandler::setKeyState(key, action);
    InputHandler::keyBuffer.push(new KeyEvent(key, scancode, action, mods));
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    InputHandler::setMouseState(button, action);
    InputHandler::mouseButtonBuffer.push(new MouseButtonEvent(button, action, mods));
}

static void character_callback(GLFWwindow* window, unsigned int codepoint) {
	InputHandler::charBuffer.push(codepoint);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	InputHandler::scrollBuffer.push(new MouseScrollEvent(xoffset, yoffset));
}

void InputHandler::setKeyState(int key, int action) {
    keyStates[key] = action;
}

void InputHandler::init() {
    glfwSetKeyCallback(WindowUtil::getWindow(), key_callback);
    glfwSetMouseButtonCallback(WindowUtil::getWindow(), mouse_button_callback);
    glfwSetCharCallback(WindowUtil::getWindow(), character_callback);
	glfwSetScrollCallback(WindowUtil::getWindow(), scroll_callback);
}

void InputHandler::update() {
	mouseState = WindowUtil::mouseState;
    KeyEvent *event;
    while(!keyBuffer.empty()) {
        event = keyBuffer.front();
        keyBuffer.pop();
        std::map<int, InputCallback*>::iterator it1 = keyCallBacks.find(event->key);
        std::map<int, InputCallback*>::iterator it2 = keyCallBacks.find(-1);
        if(it1 != keyCallBacks.end()) {
            it1->second->invoke(event->key, event->scancode, event->action, event->mods);
        } else if(it2 != keyCallBacks.end()) {
            it2->second->invoke(event->key, event->scancode, event->action, event->mods);
        }
		delete event;
    }
    MouseButtonEvent *event1;
    while(!mouseButtonBuffer.empty()) {
        event1 = mouseButtonBuffer.front();
        mouseButtonBuffer.pop();
        std::map<int, InputCallback*>::iterator it1 = mouseButtonCallbacks.find(event1->button);
        std::map<int, InputCallback*>::iterator it2 = mouseButtonCallbacks.find(-1);
        if(it1 != mouseButtonCallbacks.end()) {
            it1->second->invoke(event1->button, event1->action, event1->mods);
        } else if(it2 != mouseButtonCallbacks.end()) {
            it2->second->invoke(event1->button, event1->action, event1->mods);
        }
		delete event1;
    }
	unsigned int codepoint;
	while(!charBuffer.empty()) {
		codepoint = charBuffer.front();
		charBuffer.pop();
		if(charCallback != nullptr) {
			charCallback->invoke(codepoint);
		}
	}
	
	MouseScrollEvent *event2;
	while(!scrollBuffer.empty()) {
		event2 = scrollBuffer.front();
		scrollBuffer.pop();
		if(scrollCallback != nullptr) {
			scrollCallback->invoke(event2->xoffset, event2->yoffset);
		}
		delete event2;
	}

    glm::vec2 mouse = getMousePosition();
    float tempX = mouseX;
    float tempY = mouseY;

    mouseX = mouse.x;
    mouseY = mouse.y;

    dx = mouseX - tempX;
    dy = mouseY - tempY;
}

int InputHandler::getKeyState(int key) {
    auto it = keyStates.find(key);
    if(it != keyStates.end()){
        return it->second;
    } else {
        return 0;
    }
}

int InputHandler::getMouseState(int mouseButton) {
    auto it = mouseButtonStates.find(mouseButton);
    if(it != mouseButtonStates.end()) {
        return it->second;
    } else {
        return 0;
    }
}

void InputHandler::addKeyCallback(InputCallback *inputCallback) {
    keyCallBacks.insert(std::pair<int, InputCallback*>(inputCallback->key, inputCallback));
}

void InputHandler::addMouseButtonCallback(InputCallback *inputCallback) {
    mouseButtonCallbacks.insert(std::pair<int, InputCallback*>(inputCallback->key, inputCallback));
}

void InputHandler::addCharCallback(CharCallback *charCallback) {
    InputHandler::charCallback = charCallback;
}

void InputHandler::setScrollCallback(ScrollCallback *scrollCallback) {
	InputHandler::scrollCallback = scrollCallback;
}

glm::vec2 InputHandler::getMousePosition() {
    double xpos, ypos;
    glfwGetCursorPos(WindowUtil::getWindow(), &xpos, &ypos);
    return glm::vec2(xpos, ypos);
}

glm::vec2 InputHandler::getMouseDelta() {
    return glm::vec2(dx, dy);
}

void InputHandler::setMouseState(int mouseButton, int action) {
    mouseButtonStates[mouseButton] = action;
}
