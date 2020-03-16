#include "LevelUI.h"
#include "../../GUI/imgui.h"
#include "../../GUI/addons/imguidock/imguidock.h"
#include "../../Engine/StargazerEngine.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Entity/EntityManager.h"
#include "../../Engine/Entity/Entity.h"
#include "InspectorUI.h"
#include "EditorUI.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>

std::map<unsigned int, bool> LevelUI::entityCheckedList;

void LevelUI::renderUI() {
	EntityManager *em = StargazerEngine::getInstance().getActiveLevel()->getEntityManager();
	std::map<unsigned int, std::string> entityNameList = em->getEntityNameList();

	if(ImGui::BeginDock("Inspector")) {
		if(ImGui::TreeNode("Level")) {
			std::map<unsigned int, bool>::iterator iterator;

			int node_clicked = -1;
			for(auto & it: entityNameList) {
				iterator = entityCheckedList.find(it.first);
				if(iterator == entityCheckedList.end()) {
					entityCheckedList[it.first] = false;
				}
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | (entityCheckedList[it.first] ? ImGuiTreeNodeFlags_Selected : 0);

				ImGui::TreeNodeEx(("entity_" + std::to_string(it.first)).c_str(), node_flags, it.second.c_str());
				if(ImGui::IsItemClicked()) {
					node_clicked = it.first;
				}
			}
			if(node_clicked != -1) {
				if(ImGui::GetIO().KeyCtrl) {
					entityCheckedList[node_clicked] = true;
					Entity *entity = em->getEntity(node_clicked);
					entity->select();
					editorUI->getInspectorUI()->setAdditionalActiveEntity(entity);
				} else  {
					for(auto & it: entityCheckedList) {
						it.second = false;
						em->getEntity(it.first)->deselect();
					}
					entityCheckedList[node_clicked] = true;
					Entity *entity = em->getEntity(node_clicked);
					entity->select();
					editorUI->getInspectorUI()->setActiveEntity(entity);
				}
			}
			ImGui::TreePop();
		}

		if(ImGui::IsWindowFocused()) {
			if(ImGui::IsKeyDown(GLFW_KEY_DELETE)) {
				std::vector<unsigned int> toBeDeleted;
				for(auto & it: entityCheckedList) {
					if(it.second) {
						toBeDeleted.push_back(it.first);
						editorUI->getInspectorUI()->clearActiveEntites();
						em->removeEntity(it.first);
					}
				}
				for(auto & it: toBeDeleted) {
					entityCheckedList.erase(it);
				}
			}
		}
	}

	ImGui::EndDock();
}