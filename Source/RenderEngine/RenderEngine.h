#pragma once
#include <queue>
#include "Command\Command.h"
#include <map>
#include <vector>
#include <GLM/glm.hpp>
#include <boost/thread.hpp>

typedef unsigned int GLuint;

class Light;
class Scene;
class PostProcessor;
class FrameBuffer;
struct DrawList;
class TexturePromise;

class RenderEngine
{
public:
	static RenderEngine& getInstance() {
		static RenderEngine instance;
		return instance;
	}
	void initialize();
	void run();
	boost::mutex commandBufferMutex;
	boost::mutex cycleCommandbufferMutex;
	boost::condition_variable commandBufferCV;
	std::queue<Command*> commandBuffer;
	std::queue<Command*> recursionCommandBuffer;
	void addCommand(Command* command, bool threadSafe = true);
	bool isCommandBufferExecuting();
	void setCommandBufferExecuting(bool isExecuting);
	void cycleCommandBuffer();
	RenderEngine(RenderEngine const&) = delete;
	void operator=(RenderEngine const&) = delete;
	void executeCommandBuffer();
	std::vector<Light*> getLights() {return lights;};
	void addLight(Light *light) {lights.push_back(light);};
	void removeLight(Light *light);
	glm::vec3 getClearColor();
	void setClearColor(glm::vec3 color);
	Scene *getCurrentScene();
	void setPostProcessor(PostProcessor *postProcessor);
	void setActiveScene(Scene *scene);
	std::map<std::string, TexturePromise*> createPBRCubeMapFromHDR(std::string name, std::string path);
	void createBRDFLUT(std::string name);
	void render();
	static void clearBuffers();
	void setGuiDrawData(std::vector<DrawList*> drawList);
	GLuint getPostProcessorTexture();
	void renderToTexture(bool renderToTexture);
	void setRenderScale(glm::vec2 renderScale);
	glm::vec2 getRenderScale();
	
	bool initialized = false;
	bool imguiDevicesValid = false;
	boost::thread::id thread_id;

private:
	RenderEngine() {};
	~RenderEngine();
	bool commandBufferExecuting = false;
	std::vector<Light*> lights;
	void processCommands(std::queue<Command*> commands);
	int commandBufferRecursions;
	glm::vec3 clearColor;
	Scene *currentScene;
	PostProcessor *postProcessor = nullptr;
	FrameBuffer *fbo = nullptr;
	std::vector<DrawList*> drawlist;
	glm::vec2 renderScale;
	glm::vec2 lastRenderScale;
};

