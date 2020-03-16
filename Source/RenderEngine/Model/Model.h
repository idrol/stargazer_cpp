#pragma once

#include <GLM/glm.hpp>
#include <vector>

class Transform;
class Mesh;
class Material;

class Model {
public:
    Model();
	~Model();
    void setPositionControl(Transform *transform);
    void setRotationControl(Transform *transform);
    void setScaleControl(Transform *transform);
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);
    void setVisible(bool visible);
    bool isVisible();
    void setMaterial(Material *material);
	Material *getMaterial();
    void addMesh(Mesh* mesh);
    void enableWireframe() {wireframe = true;};
    void disableWireframe() {wireframe = false;};
    void enableCullFace() {cullFace = true;};
    void disableCullFace() {cullFace = false;};
	void enableOutline(bool outline);
    Mesh *getMesh(int i);
	std::vector<Mesh*> getMeshes();
    void draw();
    Transform* getTransform();

private:
    bool visible = true;
    bool wireframe = false;
    bool cullFace = true;
	bool drawOutline = false;
    Transform *transform;
    Transform *positionControl;
    Transform *rotationControl;
    Transform *scaleControl;
	Material *material = nullptr;
    glm::mat4 transformMatrix;
    std::vector<Mesh*> meshes;
};
