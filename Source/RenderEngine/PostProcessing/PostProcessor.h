#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh;
class ScreenRenderFilter;

class PostProcessor {
public:
	void init(GLuint texture);
	virtual void doPostProcessing(GLuint texture) {};
	void finalizeRender(GLuint texture);
	void setRenderToScreen(bool renderToScreen) {
		this->renderToScreen = renderToScreen;
	};
	GLuint getFinalImage() {
		return finalImage;
	};


protected:
	bool renderToScreen = true;
	GLuint finalImage = 0;

	void start();
	void end();

private:
	std::vector<GLfloat> quadData = {-1, 1, -1, -1, 1, 1, 1, -1};
	Mesh *mesh;
	ScreenRenderFilter *screenRenderFilter;
};