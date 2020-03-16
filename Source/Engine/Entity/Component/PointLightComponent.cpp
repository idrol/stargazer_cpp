#include "PointLightComponent.h"
#include "../Message/Message.h"
#include "../Message/TransformMessage.h"
#include "../../../RenderEngine/RenderEngine.h"
#include "../../../RenderEngine/Light/Light.h"
#include "../../../RenderEngine/Light/PointLight.h"
#include "../../../RenderEngine/Command/CompileLights.h"
#include "../../../GUI/imgui.h"

void PointLightComponent::setPointLight(PointLight *pointLight) { 
	if(this->pointLight != nullptr) {
		RenderEngine::getInstance().removeLight(this->pointLight);
	}
	RenderEngine::getInstance().addLight(pointLight);
	this->pointLight = pointLight;
	RenderEngine::getInstance().addCommand(new CompileLights());
}

void PointLightComponent::setColor(glm::vec3 color) {
	if(pointLight != nullptr) {
		pointLight->setColor(color);
		RenderEngine::getInstance().addCommand(new CompileLights());
	}
}

void PointLightComponent::setIntensity(int intensity) {
	if(pointLight != nullptr) {
		pointLight->setIntensity(intensity);
		RenderEngine::getInstance().addCommand(new CompileLights());
	}
}

glm::vec3 PointLightComponent::getColor() {
	if(pointLight != nullptr) {
		return pointLight->getColor();
	}
}

int PointLightComponent::getIntensity() {
	if(pointLight != nullptr) {
		return pointLight->getIntensity();
	}
}

void PointLightComponent::renderEditorInspector() {
	ImGui::Text("Light");

	glm::vec3 color = getColor();
	float color3[3] = {color.x, color.y, color.z};
	ImGui::ColorEdit3("Color", color3);
	glm::vec3 updatedColor(color3[0], color3[1], color3[2]);
	setColor(updatedColor);

	int intensity = getIntensity();
	ImGui::InputInt("Intensity", &intensity);
	setIntensity(intensity);
}

void PointLightComponent::sendMessage(Message *message) {
	if(message->id == "TransformMessage") {
		if(TransformMessage *transformMessage = dynamic_cast<TransformMessage*>(message)) {
			pointLight->setPosition(transformMessage->position);
			RenderEngine::getInstance().addCommand(new CompileLights());
		}
	}
}