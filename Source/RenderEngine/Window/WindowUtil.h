#pragma once
#include <GLM/vec2.hpp>

struct GLFWwindow;

class WindowUtil
{
public:
	WindowUtil();
	~WindowUtil();
	static GLFWwindow* getWindow();
	static void setTitle(char);
	static void initWindow();
	static void setGLViewport(int left, int top, int right, int bottom);
	static void setDefaultGLViewport();
	static void setMSAASamples(int samples);
	static void setGLProfile(int profile);
	static void setGLContextVersion(int major, int minor);
	static int getMSAASamples() { return msaa_samples; };
	static glm::ivec2 getFrameBufferSize();
	static glm::ivec2 getWindowSize();

	static int mouseState;
	static int getWidth();
	static int getHeight();
	static void setWidth(int width);
	static void setHeight(int height);
	static void updateWindowParameters();
	static int getWindowFocused();
	static void setMousePosition(float x, float y);
	static int getMouseMode();

private:
	static int width;
	static int height;

	//GLFW
	static GLFWwindow* window;
	static bool overrideProfile;
	static int major, minor, profile;
	static int msaa_samples;
	static int windowFocused;
	static int mouseMode;
};

