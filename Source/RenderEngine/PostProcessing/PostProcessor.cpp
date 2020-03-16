#include "PostProcessor.h"
#include "../Model/Model.h"
#include "../Model/Mesh.h"
#include "../Command/Command.h"
#include "../Command/LoadMeshData.h"
#include "../RenderEngine.h"
#include "ScreenRenderFilter.h"

void PostProcessor::init(GLuint texture) {
	mesh = new Mesh(customPrimitive);
	LoadMeshData *command = new LoadMeshData(mesh, quadData, 2);
    RenderEngine::getInstance().addCommand(command);
	screenRenderFilter = new ScreenRenderFilter();
	finalImage = texture;
}

void PostProcessor::finalizeRender(GLuint texture) {
	if(renderToScreen) {
		screenRenderFilter->render(texture);
	}
}

void PostProcessor::start() {
	glBindVertexArray(mesh->vaoID);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
}

void PostProcessor::end() {
	glEnable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}