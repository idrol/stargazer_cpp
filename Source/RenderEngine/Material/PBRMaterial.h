#pragma once

#include "Material.h"
#include <string>
#include <GLM/glm.hpp>

class Texture;

class PBRMaterial: public Material {
public:
    PBRMaterial();
    void apply() override;
    void bindTextures() override;

    void setAlbedo(glm::vec3 color);
    void setAlbedo(Texture *texture);
    void setAlbedo(std::string path);
	void clearAlbedoMap();
	glm::vec3 getAlbedo();
	bool hasAlbedoMap();
	Texture *getAlbedoMap();

    void setNormalMap(Texture *texture);
    void setNormalMap(std::string path);
	void clearNormalMap();
	bool hasNormalMap();
	Texture* getNormalMap();

    void setMetallic(float metallic);
    void setMetallic(Texture *texture);
    void setMetallic(std::string path);
	void clearMetallicMap();
	float getMetallic();
	bool hasMetallicMap();
	Texture *getMetallicMap();

    void setRoughness(float roughness);
    void setRoughness(Texture *texture);
    void setRoughness(std::string path);
	void clearRoughnessMap();
	float getRoughness();
	bool hasRoughnessMap();
	Texture *getRoughnessMap();

    void setAo(float ao);
    void setAo(Texture *texture);
    void setAo(std::string path);

protected:
    void setShaderProperties() override;


private:
    Texture *albedoMap, *normalMap, *metallicMap, *roughnessMap, *aoMap;
    glm::vec3 albedoColor = glm::vec3(0,0,0);
    float metallic = 0, roughness = 0, ao = 1;
    bool useAlbedoMap = false, useNormalMap = false, useMetallicMap = false, useRoughnessMap = false, useAoMap = false;
};
