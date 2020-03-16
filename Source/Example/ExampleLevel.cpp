#include "ExampleLevel.h"
#include "../RenderEngine/StargazerRenderEngine.h"
#include "../StargazerEngine.h"
#include "../Engine/Entity/Component/PhysicsComponent.h"
#include "../GUI/imgui.h"
#include "../GUI/imgui_impl_stargazer_update.h"
#include "../RenderEngine/Command/UpdateGuiDrawData.h"

void ExampleLevel::load() {
	PhysicsEngine::getInstance().setGravity(glm::vec3(0, -3, 0));
    /*RenderEngine::getInstance().addCommand(new LoadTexture("gun_a", "Assets\\textures\\pbr\\gun\\Cerberus_A.png"));
    RenderEngine::getInstance().addCommand(new LoadTexture("gun_n", "Assets\\textures\\pbr\\gun\\Cerberus_N.png"));
    RenderEngine::getInstance().addCommand(new LoadTexture("gun_m", "Assets\\textures\\pbr\\gun\\Cerberus_M.png"));
    RenderEngine::getInstance().addCommand(new LoadTexture("gun_r", "Assets\\textures\\pbr\\gun\\Cerberus_R.png"));
    RenderEngine::getInstance().cycleCommandBuffer();

    RenderEngine::getInstance().addLight(new PointLight(glm::vec3(0, 2, 5), glm::vec3(1,1,1), 350));

	setSkybox("newport_loft", "Assets\\textures\\hdr\\Newport_Loft_Ref.hdr", 500);

	Entity *player = entityManager->createEntity();
	Camera *camera = new Camera(75, 0.001, 1000);
	setMainCamera(camera);
	TransformComponent *transform = new TransformComponent(player);
	transform->setPosition(glm::vec3(0, 5, 5));
	CameraComponent *cameraComponent = new CameraComponent(player, camera);
	cameraComponent->listen(transform);
	SimpleKeyboardComponent *keyboardComponent = new SimpleKeyboardComponent(player);
    transform->listen(keyboardComponent);
    createGunEntity();
    createPBRSpheres();*/
}

void ExampleLevel::update(float delta) {
	Level::update(delta);
	ImGui_ImplStargazerUpdate_NewFrame();

	bool show_another_window = true;

	ImGui::Begin("Another Window", &show_another_window);
	ImGui::Text("Hello from another window!");
	ImGui::End();

	ImGui::Render();
	ImDrawData *drawData = ImGui::GetDrawData();
	std::cout << "Draw data pointer in update is " << drawData << std::endl;
	GuiDrawData *copiedDrawData = new GuiDrawData(drawData);
	std::cout << "Pointer to copied data is " << copiedDrawData << std::endl;
	RenderEngine::getInstance().addCommand(new UpdateGuiDrawData(copiedDrawData));
}

void ExampleLevel::createGunEntity() {
    Entity *gun = entityManager->createEntity();
    new TransformComponent(gun);
    ModelComponent *gunModelComponent = new ModelComponent(gun, "GunModel");
    Model *gunModel = ModelLoader::loadModel("Assets\\models\\gun.obj");

    PBRMaterial *gunMat = new PBRMaterial();
    gunMat->setAlbedo("gun_a");
    gunMat->setNormalMap("gun_n");
    gunMat->setMetallic("gun_m");
    gunMat->setRoughness("gun_r");
    gunModel->setMatrial(gunMat);
    gunModel->disableCullFace();
    gunModelComponent->setModel(gunModel);
    gun->getTransform()->setPosition(glm::vec3(0, 0, 5));
}

void ExampleLevel::createPBRSpheres() {
    Entity *plane = entityManager->createEntity();
    TransformComponent *planeTransform = new TransformComponent(plane);
    PhysicsComponent *planePhysics = new PhysicsComponent(plane);
    btCollisionShape *planeShape = new btStaticPlaneShape(btVector3(0,1,0), 1);
    planePhysics->configureStatic(planeShape, glm::vec3(0, 0, 0));
    planeTransform->listen(planePhysics);
    ModelComponent *planeModel = new ModelComponent(plane, "PlaneModel");
    Model *quadModel = shape_util::getQuadModel();
    PBRMaterial *quadMat = new PBRMaterial();
    quadMat->setAlbedo(glm::vec3(1,1,1));

    Model *gunModel = ModelLoader::loadModel("Assets\\models\\gun.obj");

    PBRMaterial *gunMat = new PBRMaterial();
    gunMat->setAlbedo("gun_a");
    gunMat->setNormalMap("gun_n");
    gunMat->setMetallic("gun_m");
    gunMat->setRoughness("gun_r");
    gunModel->setMatrial(gunMat);
    gunModel->disableCullFace();

    planeModel->setModel(gunModel);

    int nrRows = 10;
    int nrColumns = 10;
    int count = 0;

    for(int x = 0; x < nrRows; ++x) {
        for(int y = 0; y < nrColumns; ++y) {
			float random_num = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            PBRMaterial *red = new PBRMaterial();
            red->setAlbedo(glm::vec3(1, 0, 0));

            red->setMetallic((float)y/(float)nrColumns);
            float xVal = (float)(x/10);
            float yVal = (float)(y/10);
            red->setRoughness(glm::clamp((float)x/(float)nrRows, 0.05f, 1.0f));
            Model *model = shape_util::getSphereModel(1, 60, 60);
            glm::vec3 position = glm::vec3(x*2 -10, y * 2 - 10, 0);
            model->setPosition(position);
            model->setMatrial(red);

            Entity *sphere = entityManager->createEntity();
            TransformComponent *transformComponent = new TransformComponent(sphere);
            ModelComponent *sphereModelComponent = new ModelComponent(sphere, "SphereModel");
            sphereModelComponent->setModel(model);
            //PhysicsComponent *physicsComponent = new PhysicsComponent(sphere);
            //btCollisionShape *sphereShape = new btSphereShape(1);
            //physicsComponent->configureDynamic(sphereShape, position, 1);
            //transformComponent->listen(physicsComponent);
            count++;
        }
    }
}