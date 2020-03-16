#include "DebugRenderer.h"
#include "../RenderEngine/Model/Model.h"
#include "../RenderEngine/Model/Mesh.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/Command/LoadMeshData.h"
#include "../RenderEngine/Scene.h"
#include "../RenderEngine/Material/UnlitMaterial.h"
#include "../Engine/Level/Level.h"
#include <iostream>
#include <string>

DebugRenderer::DebugRenderer() {

}

void DebugRenderer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &fromColor,
                             const btVector3 &toColor) {
    drawLine(from, to, fromColor);
}

void DebugRenderer::clearDataBuffers() {
    lineData = std::vector<float>();
    triangleData = std::vector<float>();
    pointData = std::vector<float>();
    /*lineData.clear();
    std::vector<float>(lineData).swap(lineData);
    triangleData.clear();
    std::vector<float>(triangleData).swap(triangleData);
    pointData.clear();
    std::vector<float>(pointData).swap(pointData);*/
}

void DebugRenderer::finalizeRender() {
    auto *loadLines = new LoadMeshData(linesMesh, lineData, 3);
    RenderEngine::getInstance().addCommand(loadLines);
    auto *loadTriangles = new LoadMeshData(triangleMesh, triangleData, 3);
    RenderEngine::getInstance().addCommand(loadTriangles);
    auto *loadPoints = new LoadMeshData(pointsMesh, pointData, 3);
    RenderEngine::getInstance().addCommand(loadPoints);
}

DebugRenderer::~DebugRenderer() {

}

void DebugRenderer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) {
    lineData.push_back(from.x());
    lineData.push_back(from.y());
    lineData.push_back(from.z());
    lineData.push_back(to.x());
    lineData.push_back(to.y());
    lineData.push_back(to.z());
}

void DebugRenderer::drawSphere(const btVector3 &p, btScalar radius, const btVector3 &color) {
    btIDebugDraw::drawSphere(p, radius, color);
}

void DebugRenderer::drawTriangle(const btVector3 &a, const btVector3 &b, const btVector3 &c, const btVector3 &color,
                                 btScalar alpha) {
    triangleData.push_back(a.x());
    triangleData.push_back(a.y());
    triangleData.push_back(a.z());
    triangleData.push_back(b.x());
    triangleData.push_back(b.y());
    triangleData.push_back(b.z());
    triangleData.push_back(c.x());
    triangleData.push_back(c.y());
    triangleData.push_back(c.z());
}

void
DebugRenderer::drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime,
                                const btVector3 &color) {
    pointData.push_back(PointOnB.x());
    pointData.push_back(PointOnB.y());
    pointData.push_back(PointOnB.z());
}

void DebugRenderer::reportErrorWarning(const char *warningString) {
    std::string warning(warningString);
    std::cout << "[Bullet] Warning: " << warning << std::endl;
}

void DebugRenderer::draw3dText(const btVector3 &location, const char *textString) {

}

void DebugRenderer::setDebugMode(int debugMode) {

}

void DebugRenderer::registerDebugModelsToLevel(Level *level) {
    Scene *scene = level->getScene();
    scene->register3DModel(trianglesModel);
    scene->register3DModel(linesModel);
    scene->register3DModel(pointsModel);
}

void DebugRenderer::initializeModels() {
    auto *mat = new UnlitMaterial();
    mat->setDiffuseColor(glm::vec3(1,1,1));

    linesModel = new Model();
    linesMesh = new Mesh(MeshPrimitiveType::customPrimitive);
    linesMesh->renderMode = GL_LINES;
    linesModel->disableCullFace();
    linesModel->enableWireframe();
    linesModel->addMesh(linesMesh);
    linesModel->setMaterial(mat);

    trianglesModel = new Model();
    triangleMesh = new Mesh(MeshPrimitiveType::customPrimitive);
    trianglesModel->addMesh(triangleMesh);
    trianglesModel->disableCullFace();
    trianglesModel->enableWireframe();
    trianglesModel->setMaterial(mat);

    pointsModel = new Model();
    pointsMesh = new Mesh(MeshPrimitiveType::customPrimitive);
    pointsMesh->renderMode = GL_POINTS;
    pointsModel->addMesh(pointsMesh);
    pointsModel->disableCullFace();
    pointsModel->enableWireframe();
    pointsModel->setMaterial(mat);
}


