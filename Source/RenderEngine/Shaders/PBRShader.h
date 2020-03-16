#pragma once

#include "Shader.h"
#include "ILightShader.h"
#include "IShaderCamPos.h"

class PBRShader: public Shader, public ILightShader, public IShaderCamPos {
public:
    PBRShader(): Shader("Engine/shaders/generic/defaultLitPBR.shader") {};

    void registerAllUniforms() override;
    void loadTextureAddresses() override;
    void bindAttributes() override;
    void loadLights(std::vector<Light*> lights) override;
    void saveCamPos(glm::vec3 camPos) override;

    void loadAlbedo(glm::vec3 albedo);
    void loadMetallic(float metallic);
    void loadRoughness(float roughness);
    void loadAO(float ao);
    void loadUseAlbedoMap(bool flag);
    void loadUseNormalMap(bool flag);
    void loadUseMetallicMap(bool flag);
    void loadUseRoughnessMap(bool flag);
    void loadUseAOMap(bool flag);
    void loadUseIrradianceTexture(bool flag);
    void loadUsePrefilterMap(bool flag);
    void loadUseBRDFLUT(bool flag);

private:
    static const int MAX_LIGHTS = 25;
};
