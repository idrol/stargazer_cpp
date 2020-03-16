#include "ModelComponent.h"
#include "../Entity.h"
#include "../EntityManager.h"
#include "../../Level/Level.h"
#include "../../../RenderEngine/StargazerRenderEngine.h"
#include "../Message/Message.h"
#include "../Message/TransformMessage.h"
#include "../../../GUI/imgui.h"
#include "../../../RenderEngine/Material/Material.h"
#include "../../../RenderEngine/Material/PBRMaterial.h"
#include "../../../RenderEngine/Material/SkyboxMaterial.h"
#include "../../../RenderEngine/Texture/Texture.h"
#include "../../../RenderEngine/Texture/TextureManager.h"
#include "../../../RenderEngine/Texture/TexturePromise.h"

ModelComponent::~ModelComponent() {
	Scene *scene = entityHandle->getEMHandle()->getLevel()->getScene();
	if(model != nullptr) {
		std::cout << "Removing 3D model" << std::endl;
		scene->remove3DModel(model);
	}
	delete model;
}

void ModelComponent::setModel(Model *model) {
	Scene *scene = entityHandle->getEMHandle()->getLevel()->getScene();
	if(this->model != nullptr) {
		scene->remove3DModel(this->model);
	}
	scene->register3DModel(model);
	this->model = model;
}

void ModelComponent::sendMessage(Message *message) {
	if(message->id == "TransformMessage") {
		if(TransformMessage* transformMessage = dynamic_cast<TransformMessage*>(message)) {
			model->setPosition(transformMessage->position);
			model->setScale(transformMessage->scale);
			model->setRotation(transformMessage->rotation);
		}
	}
}

void ModelComponent::select() {
	if(model != nullptr) {
		model->enableOutline(true);
	}
}

void ModelComponent::deselect() {
	if(model != nullptr) {
		model->enableOutline(false);
	}
}

void ModelComponent::renderEditorInspector() {
	if(model == nullptr) return;
	int i = 0;
	for(auto & mesh: model->getMeshes()) {
		ImGui::Text(("Mesh " + std::to_string(i++)).c_str());
		if(PBRMaterial *material = dynamic_cast<PBRMaterial*>(mesh->getMaterial())) {
			ImGui::Text("Material");
			ImGui::Spacing();


			if(material->hasAlbedoMap()) {
				ImGui::Text("Albedo Map");
				Texture *texture = material->getAlbedoMap();
				ImGui::Image((void*)texture->getTextureID(), ImVec2(100, 100));
			} else {
				glm::vec3 color = material->getAlbedo();
				float color3[3] = {color.x, color.y, color.z};
				ImGui::ColorEdit3("Albedo Color", color3);
				glm::vec3 updatedColor(color3[0], color3[1], color3[2]);
				material->setAlbedo(updatedColor);
			}
            if(ImGui::BeginDragDropTarget()) {
                const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("texture", 0);
                if(payload != NULL) {
                    std::string *path = (std::string*)payload->Data;
                    Texture *texture = TextureManager::getTextureWithPath(*path);
                    material->setAlbedo(texture);
                }
                ImGui::EndDragDropTarget();
            }
			if(material->hasAlbedoMap()) {
				if(ImGui::Button("Remove Albedo texture")) {
					material->clearAlbedoMap();
				}
			}

			if(material->hasNormalMap()) {
				ImGui::Spacing();
				ImGui::Text("Normal Map");
				Texture *texture = material->getNormalMap();
				ImGui::Image((void*)texture->getTextureID(), ImVec2(100, 100));
			} else {
                ImGui::Text("Normal Map");
                ImGui::Text("Empty");
            }
            if(ImGui::BeginDragDropTarget()) {
                const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("texture", 0);
                if(payload != NULL) {
                    std::string *path = (std::string*)payload->Data;
                    Texture *texture = TextureManager::getTextureWithPath(*path);
                    material->setNormalMap(texture);
                }
                ImGui::EndDragDropTarget();
            }
			if(material->hasNormalMap()) {
				if(ImGui::Button("Remove Normal Texture")) {
					material->clearNormalMap();
				}
			}

			if(material->hasMetallicMap()) {
				ImGui::Spacing();
				ImGui::Text("Metallic Map");
				Texture *texture = material->getMetallicMap();
				ImGui::Image((void*)texture->getTextureID(), ImVec2(100, 100));
			} else {
				float metallic = material->getMetallic();
				ImGui::SliderFloat("Metallic", &metallic, 0.0F, 1.0F);
				material->setMetallic(metallic);
			}
            if(ImGui::BeginDragDropTarget()) {
                const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("texture", 0);
                if(payload != NULL) {
                    std::string *path = (std::string*)payload->Data;
                    Texture *texture = TextureManager::getTextureWithPath(*path);
                    material->setMetallic(texture);
                }
                ImGui::EndDragDropTarget();
            }
			if(material->hasMetallicMap()) {
				if(ImGui::Button("Remove Metallic Texture")) {
					material->clearMetallicMap();
				}
			}

			if(material->hasRoughnessMap()) {
				ImGui::Spacing();
				ImGui::Text("Roughness Map");
				Texture *texture = material->getRoughnessMap();
				ImGui::Image((void*)texture->getTextureID(), ImVec2(100, 100));
			} else {
				float roughness = material->getRoughness();
				ImGui::SliderFloat("Roughness", &roughness, 0.0F, 1.0F);
				material->setRoughness(roughness);
			}
            if(ImGui::BeginDragDropTarget()) {
                const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("texture", 0);
                if(payload != NULL) {
                    std::string *path = (std::string*)payload->Data;
                    Texture *texture = TextureManager::getTextureWithPath(*path);
                    material->setRoughness(texture);
                }
                ImGui::EndDragDropTarget();
            }
			if(material->hasRoughnessMap()) {
				if(ImGui::Button("Remove Roughness Texture")) {
					material->clearRoughnessMap();
				}
			}
		} else if (SkyboxMaterial *material = dynamic_cast<SkyboxMaterial*>(mesh->getMaterial())) {
			if(material->hasSkyBoxTexture()) {
				ImGui::Text("Skybox Texture");
				Texture *texture = material->getSkyBoxTexture();
				ImGui::Image((void*)texture->getTextureID(), ImVec2(100, 100));
			} else {
				ImGui::Text("Skybox Texture");
				ImGui::Text("Empty");
			}
			if(ImGui::BeginDragDropTarget()) {
				const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("HDR", 0);
				if(payload != NULL) {
					std::string *path = (std::string*)payload->Data;

					std::map<std::string, TexturePromise*> promises = RenderEngine::getInstance().createPBRCubeMapFromHDR("skybox", *path);
					RenderEngine::getInstance().cycleCommandBuffer();

					material->setSkyBoxTexture(promises["cubemap"]);
				}
				ImGui::EndDragDropTarget();
			}
			if(material->hasSkyBoxTexture()) {
				if(ImGui::Button("Remove skybox texture")){
					material->clearSkyBoxTexture();
				}
			}
		}
	}
}