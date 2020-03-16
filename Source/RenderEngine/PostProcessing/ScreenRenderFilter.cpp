#include "ScreenRenderFilter.h"
#include "SimpleShader.h"
#include "ImageRenderer.h"


ScreenRenderFilter::ScreenRenderFilter() {
    shader = new SimpleShader();
	shader->init();
    renderer = new ImageRenderer();
}

void ScreenRenderFilter::render(GLuint texture) {
    shader->start();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    renderer->renderQuad();
    shader->stop();
}