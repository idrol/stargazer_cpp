#pragma once

#include <GL/glew.h>
#include "SimpleShader.h"

class ImageRenderer;
class SimpleShader;

class ScreenRenderFilter {
public:
    ScreenRenderFilter();
    void render(GLuint texture);

protected:
    ImageRenderer *renderer;

private:
    SimpleShader *shader;
};
