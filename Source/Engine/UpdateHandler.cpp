#include "UpdateHandler.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <iostream>
#include <boost\thread.hpp>
#include "Entity\EntityManager.h"
#include "StargazerEngine.h"
#include "Level\Level.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/Command/RegisterShaderDefaults.h"
#include "../RenderEngine/Command/RegisterTextureDefaults.h"
#include "../RenderEngine/Command/SetInputMode.h"
#include "../Input/StargazerInput.h"
#include "../Physics/PhysicsEngine.h"

UpdateHandler::UpdateHandler() {

}

void UpdateHandler::run() {
	while(!RenderEngine::getInstance().initialized) {
		// Make sure render engine has initialized
	}
	initialize();
	float delta = 0;
	while (StargazerEngine::getInstance().running) {
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		this->loop(delta/1000);

		boost::this_thread::sleep_for(boost::chrono::milliseconds(16));
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> time_span = t2 - t1;
		delta = time_span.count();
	}
}

void UpdateHandler::stop() {
	StargazerEngine::getInstance().running = false;
}

void UpdateHandler::initialize()
{
	PhysicsEngine::getInstance().initialize();
	StargazerEngine::getInstance().startEngine();
	PhysicsEngine::getInstance().setGravity(glm::vec3(0, -5, 0));
	RenderEngine::getInstance().addCommand(new RegisterShaderDefaults());
	RenderEngine::getInstance().addCommand(new RegisterTextureDefaults());
	RenderEngine::getInstance().createBRDFLUT("brdfLUT");
	RenderEngine::getInstance().cycleCommandBuffer();
	StargazerEngine::getInstance().switchLevel(StargazerEngine::getInstance().getDefaultLevel());
}

void UpdateHandler::loop(float delta)
{
	InputHandler::update();
	PhysicsEngine::getInstance().update(delta);
	StargazerEngine::getInstance().getActiveLevel()->update(delta);

}
