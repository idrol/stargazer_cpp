#pragma once
#include "Component.h"
#include <string>
#include <GLM/glm.hpp>

class PointLight;

class PointLightComponent: public Component {
public:
	PointLightComponent(Entity *entity, std::string id): Component(entity, id, "PointLightComponent") {
		editorInspectorImplemented = true;
	};
	void setPointLight(PointLight *pointLight);
	void sendMessage(Message *message) override;
	void setColor(glm::vec3 color);
	void setIntensity(int intensity);
	glm::vec3 getColor();
	int getIntensity();
	void renderEditorInspector() override;
	PointLight *getPointLight() {
		return pointLight;
	};
	

private:
	PointLight *pointLight = nullptr;
};