#include "ImageRenderer.h"

#include "../Camera/FrameBuffer.h"

ImageRenderer::ImageRenderer() {

}

ImageRenderer::ImageRenderer(int width, int height) {
    this->fbo = new FrameBuffer(width, height, DepthBuffer::NONE);
}

void ImageRenderer::renderQuad() {
    if(fbo != nullptr) {
        fbo->bind();
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    if(fbo != nullptr) {
        fbo->unbind();
    }
}

GLuint ImageRenderer::getOutputTexture() {
    return fbo->getColorTexture();
}