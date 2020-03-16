#pragma once

#include <vector>

using std::vector;

class Model;
class Camera;

class Scene {
public:
    void disable3D();
    void disable2D();
    void register3DModel(Model *model);
    void register2DModel(Model *model);
	void remove3DModel(Model *model);
	void remove2DModel(Model *model);
	bool contains3DModel(Model *model);
	bool contains2DModel(Model *model);
    void setCamera(Camera *camera);
    Camera *getCamera();
    void render();
    bool isEnabled3D();
    bool isEnabled2D();

private:
    vector<Model*> models3D;
    vector<Model*> models2D;
    Camera *camera = nullptr;
    bool enable3D = true, enable2D = true;

    void prepare3D();
    void renderPass3D();
    void prepare2D();
    void renderPass2D();
    void renderModels(vector<Model*> models);
};
