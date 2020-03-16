#pragma once
#include <string>

class EntityManager;
class Entity;
class Scene;
class Camera;
class LevelScriptInstance;

class Level {
public:
	Level(std::string levelName, std::string levelFile);
	~Level() {};
	Entity *createEntity();
	Entity *getEntity(unsigned int id);
	void active();
	virtual void start(); // Level started
	virtual void load(); // Load level entites
	virtual void unload(); // Unload level
    virtual void stop(); // Level stopped
	virtual void update(float delta); // Update levele entites
	void setSkybox(std::string name, std::string hdrFile, float size);
	void setMainCamera(Camera *camera);
	void screenResized();
	Scene *getScene() {
		return scene;
	};
	EntityManager *getEntityManager() {
		return entityManager;
	};
    std::string getLevelFile() {
        return levelFile;
    };
    std::string getName() {
        return levelName;
    };
    bool isPlaying() {
    	return play;
    };
	void setScriptInstance(LevelScriptInstance *scriptInstance);
	LevelScriptInstance *getScriptInstance() {
		return scriptInstance;
	};
protected:
	EntityManager *entityManager = nullptr;
	Scene *scene = nullptr;
	Camera *mainCamera = nullptr;
    std::string levelFile, levelName;
	LevelScriptInstance *scriptInstance = nullptr;
    bool play = false;
};