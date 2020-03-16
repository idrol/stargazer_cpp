#pragma once

#include "ILightShader.h"
#include "DefaultUnlitShader.h"
#include <iostream>

class DefaultLitShader: public DefaultUnlitShader, public ILightShader {
public:
    DefaultLitShader(): DefaultUnlitShader("Engine/shaders/generic/defaultlit.shader") {
		std::cout << "Depracated don't used" << std::endl;
		exit(-1);
	};

    static const int MAX_LIGHTS = 25;

    void registerAllUniforms() override;
    void loadLights(std::vector<Light*> lights) override;
    void loadTextureAddresses() override;

    void loadUseNormal(bool useNormal);
    void loadUseSpecular(bool useSpecular);
    void loadSkyColor(glm::vec3 color);
    void loadSpecularInensity(float specular);
    void loadSpecularPower(float specularPower);
    void loadRoughness(float roughness);
    void loadReflectivity(float reflectivity);
    void loadReflectionColor(glm::vec3 color);
    void loadCameraPosition(glm::vec3 position);
};
