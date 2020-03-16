#include "PrimitivesUI.h"
#include "../../GUI/imgui.h"
#include "../../GUI/addons/imguidock/imguidock.h"
#include "../Primitives/Primitive.h"
#include "../Primitives/Sphere.h"
#include "../Primitives/Cube.h"
#include "../Primitives/Plane.h"
#include "../Primitives/LightPrimitive.h"
#include "../Primitives/Player.h"
#include "../../RenderEngine/Texture/Texture.h"
#include "../Primitives/SkyboxPrimitive.h"

PrimitivesUI::PrimitivesUI(EditorUI *editorUI)  {
	this->editorUI = editorUI;
	sphere = new Sphere(this);
	light = new LightPrimitive(this);
	cube = new Cube(this);
	plane = new Plane(this);
	player = new Player(this);
	skybox = new SkyboxPrimitive(this);
}

void PrimitivesUI::renderUI() {
	if(ImGui::BeginDock("Primitives")) {
		if(ImGui::ImageButton((void*)cube->getPrimitiveIcon()->getTextureID(), ImVec2(100, 100))) {
			cube->createPrimitiveEntity();
		}
		ImGui::SameLine();
		ImGui::Text("Cube");

		if(ImGui::ImageButton((void*)plane->getPrimitiveIcon()->getTextureID(), ImVec2(100, 100))) {
			plane->createPrimitiveEntity();
		}
		ImGui::SameLine();
		ImGui::Text("Plane");

		if(ImGui::ImageButton((void*)sphere->getPrimitiveIcon()->getTextureID(), ImVec2(100, 100))) {
			sphere->createPrimitiveEntity();
		}
		ImGui::SameLine();
		ImGui::Text("Sphere");

		if(ImGui::ImageButton((void*)light->getPrimitiveIcon()->getTextureID(), ImVec2(100, 100))) {
			light->createPrimitiveEntity();
		}
		ImGui::SameLine();
		ImGui::Text("Point Light");

		if(ImGui::ImageButton((void*)player->getPrimitiveIcon()->getTextureID(), ImVec2(100, 100))) {
			player->createPrimitiveEntity();
		}
		ImGui::SameLine();
		ImGui::Text("Player");

		if(ImGui::ImageButton((void*)skybox->getPrimitiveIcon()->getTextureID(), ImVec2(100, 100))) {
			skybox->createPrimitiveEntity();
		}
		ImGui::SameLine();
		ImGui::Text("SkyBox");
	}

	ImGui::EndDock();
}