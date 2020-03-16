#pragma once

#include <GL/glew.h>
#include "../Camera/DepthBuffer.h"

class FrameBuffer {
public:
    FrameBuffer(int width, int height, DepthBuffer depthBuffer);
	~FrameBuffer();
    GLuint getColorTexture();
    GLuint getDepthTexture();
    GLuint getDepthBuffer();
    void bind();
    FrameBuffer *finnish();
    void unbind();
	void resize(int width, int height);
    void createFrameBuffer(DepthBuffer depthBuffer);
    FrameBuffer *createColorTextureAttachment();
    FrameBuffer *createDepthTextureAttachment();
    FrameBuffer *createDepthBufferAttachment();
    FrameBuffer *createColorAttachment(int width, int height);
    FrameBuffer *createDepthTextureAttachment(int width, int height);
    GLuint createTextureAttachment(int width, int height, GLint internalFormat, GLenum format, GLenum type, GLenum attachment);
    FrameBuffer *createDepthBufferAttachment(int width, int height);

private:
    int width, height;
    GLuint framebuffer = 0;
    GLuint texture = 0;
    GLuint depthTexture = 0;
    GLuint depthBufferHandle = 0;
	DepthBuffer depthBuffer;
};


