#include "StargazerApplication.h"
#include <iostream>
#include "../Lib/SetupLibs.h"
#include "../RenderEngine/RenderEngine.h"
#include "StargazerEngine.h"

StargazerApplication::StargazerApplication(UpdateHandler *updateHandler)
{
	//FreeConsole();
	this->updateHandler = updateHandler;
	RenderEngine::getInstance().initialize();
	StargazerEngine::getInstance().setRenderEngine(&RenderEngine::getInstance());
	start();
}

void StargazerApplication::start() {
	updateThreadHandle = boost::thread(boost::bind(&StargazerApplication::startUpdateHandlerThread, this));
	RenderEngine::getInstance().run();
	stopEngine();
}

void StargazerApplication::stopEngine() {
	updateHandler->stop();
	updateThreadHandle.join();
}

void StargazerApplication::startUpdateHandlerThread() {
	updateHandler->run();
}


StargazerApplication::~StargazerApplication()
{

}
