#pragma once

#include "../Engine/Level/Level.h"

class EditorCamera;
class Project;

class EditorLevel: public Level {
public:
	EditorLevel(Project *project, std::string levelName, std::string levelFile);
	void load() override;
	void unload() override;
	void update(float delta) override;
	void stop() override;

private:
	void createEditorGrid();
	bool playing = false;
	EditorCamera *editorCamera = nullptr;
	Project *project = nullptr;
};