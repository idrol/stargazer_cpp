#pragma once

#include <string>
#include <map>

class RenderEngine;
class EntityManager;
class Level;

class StargazerEngine {
public:
	StargazerEngine() {};
	// Singleton
	static StargazerEngine &getInstance() {
		static StargazerEngine instance;
		return instance;
	}
	StargazerEngine(StargazerEngine const&) = delete;
	void operator=(StargazerEngine const&) = delete;

	void setRenderEngine(RenderEngine *renderEngine) {
		this->renderEngine = renderEngine;
	};
	EntityManager *getEntityManager();
	RenderEngine *getRenderEngine() {
		return renderEngine;
	};
	void addLevel(std::string name, Level *level) {
		levels[name] = level;
	};
	Level *getLevel(std::string name);
	void removeLevel(std::string name);
	void switchLevel(Level *level);
	void setDefaultLevel(std::string level) {
		this->defaultLevel = getLevel(level);
	};
	Level *getDefaultLevel() {
		return defaultLevel;
	};
	Level *getActiveLevel() {
		return level;
	};
	void startEngine();
	void shutdownEngine();
	bool running = true;

private:
	RenderEngine *renderEngine;
	std::map<std::string, Level*> levels;
	Level *level;
	Level *defaultLevel;
};