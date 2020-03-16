#include "EditorApplication.h"
#include "../RenderEngine/RenderEngine.h"
#include "../Engine/StargazerEngine.h"

EditorApplication::EditorApplication(EditorUpdateHandler *updateHandler) {
	this->updateHandler = updateHandler;
	RenderEngine::getInstance().initialize();
	StargazerEngine::getInstance().setRenderEngine(&RenderEngine::getInstance());
	start();
}

void EditorApplication::start() {
	updateThreadHandle = boost::thread(boost::bind(&EditorApplication::startUpdateHandlerThread, this));
	RenderEngine::getInstance().run();
	stopEngine();
}

void EditorApplication::stopEngine() {
	updateHandler->stop();
	updateThreadHandle.join();
}

void EditorApplication::startUpdateHandlerThread() {
	updateHandler->run();
}