#pragma once

class LevelUI;
class InspectorUI;
class PrimitivesUI;
class AssetBrowserUI;

class EditorUI {
public:
	EditorUI();
	void update(float delta);
	InspectorUI *getInspectorUI();
	LevelUI *getLevelUI();
	PrimitivesUI *getPrimitivesUI();
	AssetBrowserUI *getAssetBrowserUI();

private:
	void prepareGui(float delta);
	void renderGui();
	void finalizeGui();
	bool isEditorWindowFocused = false;

	LevelUI *levelUI = nullptr;
	InspectorUI *inspectorUI = nullptr;
	PrimitivesUI *primitivesUI = nullptr;
	AssetBrowserUI *assetBrowserUI = nullptr;
};