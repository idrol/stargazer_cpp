#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Window\WindowUtil.h"
#include "RenderEngine.h"
#include <iostream>
#include "Scene.h"
#include "Camera/Camera.h"
#include "Shaders/ShaderManager.h"
#include "../Util/stargazer_util.h"
#include "Command/CompileLights.h"
#include "../Input/InputHandler.h"

#include "Command/ConvertHDRToCubeMap.h"
#include "Command/GenerateIrradianceMapFromCubeMap.h"
#include "Command/SetIrradianceTexture.h"
#include "Command/PrefilterCubeMap.h"
#include "Command/GenerateBRDFLUT.h"
#include "Command/SetBRDFLUT.h"
#include "Command/SetPrefilterMap.h"
#include "Command/LoadHDRTexture.h"
#include "Command/SetInputMode.h"
#include "../Util/shape_util.h"
#include "Camera/FrameBuffer.h"
#include "PostProcessing/PostProcessor.h"
#include "PostProcessing/DefaultPostProcessor.h"
#include "../Engine/StargazerEngine.h"
#include "../Engine/Level/Level.h"
#include "../GUI/imgui.h"
#include "../GUI/imgui_impl_stargazer_render.h"
#include "Command/LoadTexture.h"
#include "Texture/TextureManager.h"
#include "Texture/TexturePromise.h"

void RenderEngine::initialize() {
	std::cout << "[RenderEngine] " << "Initializing render engine" << std::endl;
	thread_id = boost::this_thread::get_id();
	WindowUtil::initWindow();
	TextureManager::initialize();
}

void RenderEngine::setGuiDrawData(std::vector<DrawList*> drawlist) {
	if(!this->drawlist.empty()) {
		for(const auto drawcall: this->drawlist) {
			delete drawcall;
		}
		this->drawlist.clear();
	}
	this->drawlist = drawlist;
}

void RenderEngine::clearBuffers() {
	glStencilMask(0xFF);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glStencilMask(0x00);
}

void RenderEngine::run() {
	renderScale = glm::vec2(WindowUtil::getWidth(), WindowUtil::getHeight());
	lastRenderScale = renderScale;
	InputHandler::init();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glm::ivec2 fbSize = WindowUtil::getFrameBufferSize();
    fbo = new FrameBuffer(renderScale.x, renderScale.y, DepthBuffer::DEPTH_BUFFER);
    if(postProcessor == nullptr) setPostProcessor(new DefaultPostProcessor());

	ImGui_ImplStargazerRender_Init(WindowUtil::getWindow(), false);
	ImGui::StyleColorsClassic();
	ImGui_ImplStargazerRender_CreateDeviceObjects();
	imguiDevicesValid = true;
	executeCommandBuffer();
	std::cout << "[RenderEngine] Finnished loading starting render loop" << std::endl;
	initialized = true;
    do {
		clearBuffers();
		WindowUtil::updateWindowParameters();
		glViewport(0, 0, renderScale.x, renderScale.y);
		if(lastRenderScale != renderScale) {
			if(StargazerEngine::getInstance().getActiveLevel() != nullptr) {
				StargazerEngine::getInstance().getActiveLevel()->screenResized();
			}
			fbo->resize(renderScale.x, renderScale.y);
		}
		lastRenderScale = renderScale;
		addCommand(new CompileLights());
		executeCommandBuffer();
        fbo->bind();
		render();
        fbo->unbind();
        postProcessor->doPostProcessing(fbo->getColorTexture());

		if(!drawlist.empty()) {
			ImGui_ImplStargazerRender_RenderDrawLists(drawlist);
		}

		glfwSwapBuffers(WindowUtil::getWindow());
		glfwPollEvents();
        boost::lock_guard<boost::mutex> lk(cycleCommandbufferMutex);
        commandBufferCV.notify_one();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(16));
	} while (glfwWindowShouldClose(WindowUtil::getWindow()) == 0 && StargazerEngine::getInstance().running);
	imguiDevicesValid = false;
	ImGui_ImplStargazerRender_Shutdown();
}

void RenderEngine::removeLight(Light *light) {
	std::vector<Light*>::iterator it = std::find(lights.begin(), lights.end(), light);
	if(it != lights.end()) {
		lights.erase(it);
	}
}

void RenderEngine::addCommand(Command* command, bool threadSafe)
{
	if(thread_id != boost::this_thread::get_id()) {
		commandBufferMutex.lock();
	} else {
		if (isCommandBufferExecuting()) {
			recursionCommandBuffer.push(command);
			return;
		}
		commandBufferMutex.lock();
	} 
    commandBuffer.push(command);
    commandBufferMutex.unlock();
}

bool RenderEngine::isCommandBufferExecuting()
{
	return commandBufferExecuting;
}

void RenderEngine::setCommandBufferExecuting(bool isExecuting)
{
    commandBufferExecuting = isExecuting;
}

void RenderEngine::cycleCommandBuffer()
{
	boost::unique_lock<boost::mutex> lk(cycleCommandbufferMutex);
    commandBufferCV.wait(lk);
}

void RenderEngine::executeCommandBuffer()
{
	commandBufferMutex.lock();
	if(commandBuffer.empty()) {
		commandBufferMutex.unlock();
		return;
	}
    setCommandBufferExecuting(true);
    std::queue<Command*> commands = commandBuffer;

	std::queue<Command*> empty;
	std::swap(commandBuffer, empty);

    processCommands(commands);
	commandBufferMutex.unlock();
    commandBufferRecursions++;
    while (recursionCommandBuffer.size() != 0) {
        if (commandBufferRecursions >= 16) {
            std::cout << "[RenderEngine] " << "Recursive command buffer execution limit reached! EXITING" << std::endl;
            exit(-1);
        }
		// problem with syncronization becuase addcommand from update will get added to recursion buffer while this runns and cause crash but putting lock before recursion check cuases deadlock
        std::queue<Command*> recursionCommands = recursionCommandBuffer;
        recursionCommandBuffer = *new std::queue<Command*>();
        processCommands(recursionCommands);
        commandBufferRecursions++;
		std::queue<Command*>().swap(recursionCommands);
    }
    commandBufferRecursions = 0;
    setCommandBufferExecuting(false);
	std::queue<Command*>().swap(commands);
}

void RenderEngine::processCommands(std::queue<Command*> commands)
{
	while (!commands.empty()) {
		Command *command = commands.front();
		command->execute();
		commands.pop();
		delete command;
	}
}


RenderEngine::~RenderEngine()
{
}

glm::vec3 RenderEngine::getClearColor() {
	return clearColor;
}

void RenderEngine::setClearColor(glm::vec3 color) {
	clearColor = color;
}

Scene *RenderEngine::getCurrentScene() {
	return currentScene;
}

void RenderEngine::setActiveScene(Scene *scene) {
	currentScene = scene;
}

void RenderEngine::render() {
	if (currentScene != nullptr)  {
		// Scene can only be rendered if camera is present
        if (currentScene->getCamera() != nullptr) {
            ShaderManager::reloadViewMatrix(stargazer_util::createViewMatrix(currentScene->getCamera()));
            ShaderManager::saveCamPos(currentScene->getCamera()->getPosition());
			stargazer_util::clear();
			currentScene->render();
        }
    }
}

std::map<std::string, TexturePromise*> RenderEngine::createPBRCubeMapFromHDR(std::string name, std::string path) {
	std::map<std::string, TexturePromise*> promises;

	auto *loadHDRTexture = new LoadHDRTexture(name, path);
	promises["hdrTexture"] = loadHDRTexture->getTexturePromise();
	addCommand(loadHDRTexture);

	auto *convertHDRToCubeMap = new ConvertHDRToCubeMap(name + "_cubemap", name, shape_util::getCubeModel(), path);
	promises["cubemap"] = convertHDRToCubeMap->getTexturePromise();
	addCommand(convertHDRToCubeMap);

	auto *generateIrradiance = new GenerateIrradianceMapFromCubeMap(name + "_irradiance", name + "_cubemap", shape_util::getCubeModel(), path);
	promises["irradiance"] = generateIrradiance->getTexturePromise();
	addCommand(generateIrradiance);

	addCommand(new SetIrradianceTexture(name + "_irradiance"));

	auto *prefilter = new PrefilterCubeMap(name + "_prefilter", name + "_cubemap", shape_util::getCubeModel(), path);
	promises["prefilter"] = prefilter->getTexturePromise();
	addCommand(prefilter);

	addCommand(new SetPrefilterMap(name + "_prefilter"));

	return promises;
}

void RenderEngine::createBRDFLUT(std::string name) {
	addCommand(new GenerateBRDFLUT(name, shape_util::getQuadModel()));
	addCommand(new SetBRDFLUT(name));
}

void RenderEngine::setPostProcessor(PostProcessor *postProcessor) {
    this->postProcessor = postProcessor;
    this->postProcessor->init(fbo->getColorTexture());
}

GLuint RenderEngine::getPostProcessorTexture() {
	return postProcessor->getFinalImage();
}

void RenderEngine::renderToTexture(bool renderToTexture) {
	postProcessor->setRenderToScreen(!renderToTexture);
}

void RenderEngine::setRenderScale(glm::vec2 renderScale) {
	this->renderScale = renderScale;
}

glm::vec2 RenderEngine::getRenderScale() {
	return renderScale;
}