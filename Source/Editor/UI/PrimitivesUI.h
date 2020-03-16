#pragma once

class EditorUI;
class Cube;
class Plane;
class Sphere;
class LightPrimitive;
class Player;
class SkyboxPrimitive;

class PrimitivesUI {
public:
	PrimitivesUI(EditorUI *editorUI);
	void renderUI();

private:
	EditorUI *editorUI = nullptr;
	Cube *cube = nullptr;
	Plane *plane = nullptr;
	Sphere *sphere = nullptr;
	LightPrimitive *light = nullptr;
	Player *player = nullptr;
	SkyboxPrimitive *skybox = nullptr;
};