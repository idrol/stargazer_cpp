#pragma once
#include <vector>

class Entity;
class EditorUI;

class InspectorUI {
public:
	InspectorUI(EditorUI *editorUI) {
		this->editorUI = editorUI;
	};
	void setActiveEntity(Entity *entity);
	void setActiveEntity(std::vector<Entity*> activeEntites);
	void clearActiveEntites();
	void setAdditionalActiveEntity(Entity *entity);
	void renderUI();

private:
	std::vector<Entity*> activeEntites;
	EditorUI *editorUI;
};