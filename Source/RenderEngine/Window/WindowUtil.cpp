#include "GL/glew.h"
#include <GLFW\glfw3.h>
#include "WindowUtil.h"
#include <iostream>

int WindowUtil::width = 1024;
int WindowUtil::height = 768;
bool WindowUtil::overrideProfile = true;
int WindowUtil::major = 3;
int WindowUtil::minor = 3;
int WindowUtil::profile = GLFW_OPENGL_CORE_PROFILE;
int WindowUtil::msaa_samples = 0;
GLFWwindow* WindowUtil::window = NULL;
int WindowUtil::mouseState = GLFW_CURSOR_NORMAL;
int WindowUtil::windowFocused = 0;
int WindowUtil::mouseMode = 0;

WindowUtil::WindowUtil()
{
}


WindowUtil::~WindowUtil()
{
}

GLFWwindow* WindowUtil::getWindow()
{
	return WindowUtil::window;
}

void WindowUtil::setTitle(char)
{
}


void error_callback(int error, const char* description) {
	std::cout << error << " " << description << std::endl;
}

void window_size_callback(GLFWwindow *window, int width, int height) {
	WindowUtil::setWidth(width);
	WindowUtil::setHeight(height);
}

void WindowUtil::initWindow()
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		std::cerr << "Unable to initialize glfw" << std::endl;
		exit(-1);
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, msaa_samples);
	if (overrideProfile) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
	}

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwWindowHint(GLFW_RED_BITS, vidMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, vidMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, vidMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);

	window = glfwCreateWindow(width, height, "Stargazer", NULL, NULL);
	// Windowed fullscreen
	// window = glfwCreateWindow(vidMode->width, vidMode->height, "Stargazer", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	

	int pWidth;
	int pHeight;
	glfwGetWindowSize(window, &pWidth, &pHeight);

	glfwSetWindowPos(
		window,
		(vidMode->width - pWidth) / 2,
		(vidMode->height - pHeight) / 2
		);

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwShowWindow(window);

	setDefaultGLViewport();
}

int WindowUtil::getWidth() {
	return width;
}

int WindowUtil::getHeight() {
	return height;
}

void WindowUtil::setWidth(int width) {
	WindowUtil::width = width;
}

void WindowUtil::setHeight(int height) {
	WindowUtil::height = height;
}

void WindowUtil::setGLViewport(int left, int top, int right, int bottom)
{
	glViewport(left, top, right, bottom);
}

void WindowUtil::setDefaultGLViewport() {
	glm::ivec2 vec = getFrameBufferSize();
	int height, width;
	glfwGetWindowSize(window, &width, &height);
	WindowUtil::setGLViewport(0, 0, vec.x, vec.y);
}

void WindowUtil::setMSAASamples(int samples)
{
	msaa_samples = samples;
}

void WindowUtil::setGLProfile(int profile)
{
	WindowUtil::profile = profile;
}

void WindowUtil::setGLContextVersion(int major, int minor)
{
	WindowUtil::major = major;
	WindowUtil::minor = minor;
}

glm::ivec2 WindowUtil::getFrameBufferSize()
{
	glm::ivec2 vec;
	glfwGetFramebufferSize(window, &vec.x, &vec.y);
	return vec;
}

glm::ivec2 WindowUtil::getWindowSize()
{
	glm::ivec2 vec;
	glfwGetWindowSize(window, &vec.x, &vec.y);
	return vec;
}

void WindowUtil::updateWindowParameters() {
	windowFocused = glfwGetWindowAttrib(window, GLFW_FOCUSED);
	mouseMode = glfwGetInputMode(window, GLFW_CURSOR);
}

int WindowUtil::getWindowFocused() {
	return windowFocused;
}

void WindowUtil::setMousePosition(float x, float y) {
	glfwSetCursorPos(window, x, y);
}

int WindowUtil::getMouseMode() {
	return mouseMode;
}