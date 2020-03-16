#pragma once

#include <GL/glew.h>

class FrameBuffer;

class ImageRenderer {
public:
    ImageRenderer(int width, int height);
    ImageRenderer();
    void renderQuad();
    GLuint getOutputTexture();

private:
    FrameBuffer *fbo = nullptr;
};

