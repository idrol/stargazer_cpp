#include "FrameBuffer.h"
#include <GLM/glm.hpp>
#include "../Window/WindowUtil.h"
#include "../RenderEngine.h"

FrameBuffer::FrameBuffer(int width, int height, DepthBuffer depthBuffer) {
    this->width = width;
    this->height = height;
    createFrameBuffer(depthBuffer);
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &depthTexture);
	glDeleteRenderbuffers(1, &depthBufferHandle);
}

GLuint FrameBuffer::getColorTexture() {
    return texture;
}

GLuint FrameBuffer::getDepthTexture() {
    return depthTexture;
}

GLuint FrameBuffer::getDepthBuffer() {
    return depthBufferHandle;
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	if(depthBuffer != DepthBuffer::NONE) {
		RenderEngine::clearBuffers();
	}
	glViewport(0, 0, width, height);
}

FrameBuffer *FrameBuffer::finnish() {
    unbind();
    return this;
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    WindowUtil::setDefaultGLViewport();
}

void FrameBuffer::createFrameBuffer(DepthBuffer depthBuffer) {
    glGenFramebuffers(1, &framebuffer);
	this->depthBuffer = depthBuffer;
    resize(width, height);
}

void FrameBuffer::resize(int width, int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	this->width = width;
	this->height = height;
	if(texture != 0) {
		glDeleteTextures(1, &texture);
	}
	if(depthTexture != 0) {
		glDeleteTextures(1, &depthTexture);
	}
	if(depthBufferHandle != 0) {
		glDeleteRenderbuffers(1, &depthBufferHandle);
	}
	createColorAttachment(width, height);
	if(depthBuffer == DepthBuffer::DEPTH_TEXTURE) {
		createDepthTextureAttachment(width, height);
	} else if(depthBuffer == DepthBuffer::DEPTH_BUFFER) {
		createDepthBufferAttachment(width, height);
	}
	unbind();
}

FrameBuffer *FrameBuffer::createColorTextureAttachment() {return createColorAttachment(width, height);}

FrameBuffer *FrameBuffer::createDepthTextureAttachment() {return createDepthTextureAttachment(width, height);}

FrameBuffer *FrameBuffer::createDepthBufferAttachment() {return createDepthBufferAttachment(width, height);}

FrameBuffer *FrameBuffer::createColorAttachment(int width, int height) {
    texture = createTextureAttachment(width, height, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0);
    return this;
}

FrameBuffer *FrameBuffer::createDepthTextureAttachment(int width, int height) {
    depthTexture = createTextureAttachment(width, height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, GL_DEPTH_STENCIL_ATTACHMENT);
    return this;
}

GLuint FrameBuffer::createTextureAttachment(int width, int height, GLint internalFormat, GLenum format, GLenum type,
                                            GLenum attachment) {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture, 0);
    return texture;
}

FrameBuffer *FrameBuffer::createDepthBufferAttachment(int width, int height) {
    glGenRenderbuffers(1, &depthBufferHandle);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferHandle);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBufferHandle);
    return this;
}