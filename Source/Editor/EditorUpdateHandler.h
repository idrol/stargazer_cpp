#pragma once

class EditorUI;
class ProjectManager;

class EditorUpdateHandler {
public:
	EditorUpdateHandler();
	void initialize();
	void loop(float delta);
	void run();
	void stop();

private:
	EditorUI *ui = nullptr;
	ProjectManager *projectManager = nullptr;
};