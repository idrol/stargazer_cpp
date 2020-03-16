#pragma once

#include "LinearMath/btIDebugDraw.h"
#include <vector>

class Model;
class Mesh;
class Level;

class DebugRenderer : public btIDebugDraw {
    int m_debugMode;

public:
    DebugRenderer();
    ~DebugRenderer() override;
    void initializeModels();
    void clearDataBuffers();
    void finalizeRender();
    void   drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) override;
    void   drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
    void   drawSphere(const btVector3& p, btScalar radius, const btVector3& color) override;
    void   drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha) override;
    void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
    void   reportErrorWarning(const char* warningString) override;
    void   draw3dText(const btVector3& location, const char* textString) override;
    void   setDebugMode(int debugMode) override;
    int getDebugMode() const override { return m_debugMode; }
    void registerDebugModelsToLevel(Level *level);

private:
    Model *linesModel = nullptr;
    Model *spheresModel = nullptr;
    Model *trianglesModel = nullptr;
    Model *pointsModel = nullptr;
    Mesh *linesMesh = nullptr;
    Mesh *triangleMesh = nullptr;
    Mesh *pointsMesh = nullptr;
    std::vector<float> lineData;
    std::vector<float> triangleData;
    std::vector<float> pointData;

};


