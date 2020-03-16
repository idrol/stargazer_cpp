#include "InspectorUI.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/Entity/Component/TransformComponent.h"
#include "../../GUI/imgui.h"
#include "../../GUI/addons/imguidock/imguidock.h"
#include <GLM\glm.hpp>

void InspectorUI::setActiveEntity(Entity *entity) {
	activeEntites.clear();
	activeEntites.push_back(entity);
}

void InspectorUI::setActiveEntity(std::vector<Entity*> activeEntites) {
	this->activeEntites.clear();
	this->activeEntites = activeEntites;
}

void InspectorUI::clearActiveEntites() {
	this->activeEntites.clear();
}

void InspectorUI::setAdditionalActiveEntity(Entity *entity) {
	activeEntites.push_back(entity);
}

void InspectorUI::renderUI() {
	if(ImGui::BeginDock("Details")) {
		if(!activeEntites.empty()) {
			if(activeEntites.size() == 1) {
				Entity *entity = activeEntites[0];
				ImGui::Text(entity->getName().c_str());
				for(auto & component: entity->getComponents()) {
					if(component.second->editorInspectorImplemented) {
						ImGui::Separator();
						component.second->renderEditorInspector();
					}
				}
			} else {
				ImGui::Text("Multiple selected");
				/*
				ImGui::Separator();
				ImGui::Text("Transform");

				glm::vec3 allPosition(0,0,0);
				glm::vec3 allScale(0,0,0);
				glm::vec3 allRotation(0,0,0);
				bool first = true;
				bool samePosition = true;
				bool sameScale = true;
				bool sameRotation = true;
				for(auto & entity: activeEntites) {
					if(first) {
						glm::vec3 position = entity->getTransform()->getPosition();
						glm::vec3 scale = entity->getTransform()->getScale();
						glm::vec3 rotation = entity->getTransform()->getRotation();
						allPosition = position;
						allScale = scale;
						allRotation = rotation;
						first = false;
					} else {
						glm::vec3 position = entity->getTransform()->getPosition();
						glm::vec3 scale = entity->getTransform()->getScale();
						glm::vec3 rotation = entity->getTransform()->getRotation();
						if(allPosition != position) {
							samePosition = false;
						}
						if(allScale != scale) {
							sameScale = false;
						}
						if(allRotation != rotation) {
							sameRotation = false;
						}
					}
					if(!samePosition && !sameRotation && !sameScale) {
						break;
					}
				}

				if(samePosition) {
					float pos3[3] = {allPosition.x, allPosition.y, allPosition.z};
					ImGui::InputFloat3("Position", pos3);
					glm::vec3 updatedPosition(pos3[0], pos3[1], pos3[2]);
					for(auto & entity: activeEntites) {
						entity->getTransform()->setPosition(updatedPosition);
					}
				} else {
					// Todo show multiple in input box but allow setting same value
					ImGui::Text("Multiple positions exists");
				}
				
				if(sameScale) {
					float scale3[3] = {allScale.x, allScale.y, allScale.z};
					ImGui::InputFloat3("Scale", scale3);
					glm::vec3 updatedScale(scale3[0], scale3[1], scale3[2]);
					for(auto & entity: activeEntites) {
						entity->getTransform()->setScale(updatedScale);
					}
				} else {
					ImGui::Text("Multiple scales exists");
				}

				if(sameRotation) {
					float rot3[3] = {allRotation.x, allRotation.y, allRotation.z};
					ImGui::InputFloat3("Rotation", rot3);
					glm::vec3 updatedRotation(rot3[0], rot3[1], rot3[2]);
					for(auto & entity: activeEntites) {
						entity->getTransform()->setRotation(updatedRotation);
					}
				} else {
					ImGui::Text("Multiple rotations exists");
				}*/
			}
		}
	}

	ImGui::EndDock();
}