#pragma once
#include <map>

class EditorUI;

class LevelUI {
public:
	LevelUI(EditorUI *editorUI) {
		this->editorUI = editorUI;
	};
	void renderUI();

	static std::map<unsigned int, bool> entityCheckedList;

private:
	EditorUI *editorUI;
};