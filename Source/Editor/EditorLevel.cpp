#include "EditorLevel.h"
#include "../RenderEngine/StargazerRenderEngine.h"
#include "../StargazerEngine.h"
#include "../GUI/imgui.h"
#include "../GUI/imgui_impl_stargazer_update.h"
#include "../RenderEngine/Command/UpdateGuiDrawData.h"
#include "../Engine/Entity/Component/PointLightComponent.h"
#include "../Physics/PhysicsEngine.h"
#include "../ResourceManager/ResourceManager.h"
#include "EditorCamera.h"
#include "Project/Project.h"
#include "../RenderEngine/Command/LoadMeshData.h"
#include "../RenderEngine/Material/UnlitMaterial.h"
#include "../Physics/DebugRenderer.h"
#include "../Engine/Scripting/ScriptingEngine.h"

void EditorLevel::load() {
    ScriptingEngine::getInstance().initialize();
	Level::load();

    Camera *camera = new Camera(75, 0.001F, 1000.0F);
    editorCamera = new EditorCamera(camera);
    scene->setCamera(camera);

    createEditorGrid();

    PhysicsEngine::getInstance().getDebugRenderer()->registerDebugModelsToLevel(this);
}

void EditorLevel::update(float delta) {
    if(play) {
        Level::update(delta);
    } else {
        editorCamera->update(delta);
    }
    PhysicsEngine::getInstance().drawDebugWorld(delta);
}

void EditorLevel::stop() {
    Level::stop();
    scene->setCamera(editorCamera->getCamera());
}

EditorLevel::EditorLevel(Project *project, std::string levelName, std::string levelFile): Level(levelName, levelFile) {
	this->project = project;
}

void EditorLevel::unload() {
    Level::unload();
}

void EditorLevel::createEditorGrid() {
    std::vector<float> vertices;
    int size = 100;
    int pos = -(size / 2);

    for(int i = 0; i<=size; i++) {
        vertices.push_back(pos + i);
        vertices.push_back(0);
        vertices.push_back(-size/2);

        vertices.push_back(pos + i);
        vertices.push_back(0);
        vertices.push_back(size/2);

        vertices.push_back(-size/2);
        vertices.push_back(0);
        vertices.push_back(pos + i);

        vertices.push_back(size/2);
        vertices.push_back(0);
        vertices.push_back(pos + i);
    }

    Mesh *mesh = new Mesh(customPrimitive);
    mesh->renderMode = GL_LINES;
    LoadMeshData *loadMeshData = new LoadMeshData(mesh, vertices, 3);
    RenderEngine::getInstance().addCommand(loadMeshData);
    Model *model = new Model();
    model->addMesh(mesh);
    UnlitMaterial *mat = new UnlitMaterial();
    mat->setDiffuseColor(glm::vec3(0.7F, 0.7F, 0.7F));
    model->setMaterial(mat);
    scene->register3DModel(model);
}

