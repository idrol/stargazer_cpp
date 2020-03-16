#pragma once
#include "Component.h"
#include <string>

class Model;

class ModelComponent: public Component {
public:
	ModelComponent(Entity *entity, std::string id): Component(entity, id, "ModelComponent") {
		editorInspectorImplemented = true;
	};
	~ModelComponent();
	void setModel(Model *model);
	void sendMessage(Message *message) override;
	void select() override;
	void deselect() override;
	void renderEditorInspector() override;
	Model *getModel() {
		return model;
	};

private:
	Model *model = nullptr;
};