//
// Created by Idrol on 29-09-2017.
//

#include <iostream>
#include "ShaderManager.h"
#include "DefaultLitShader.h"
#include "DefaultUnlitShader.h"
#include "PBRShader.h"
#include "OrthoGraphicShader.h"
#include "SkyBoxShader.h"
#include "EquirectangularShader.h"
#include "IrradianceShader.h"
#include "PrefilterShader.h"
#include "BRDFShader.h"
#include "ObjectOutlineShader.h"
#include "../RenderEngine.h"
#include <GLM/ext.hpp>

std::map<std::string, Shader*> ShaderManager::shaders;
std::vector<ILightShader*> ShaderManager::lightShaders;

void ShaderManager::registerDefaults() {
    std::cout << "[ShaderManager] Registering default shader programs" << std::endl;

    DefaultUnlitShader *defaultUnlitShader = new DefaultUnlitShader();
    defaultUnlitShader->init();
    registerShader("defaultUnlit", defaultUnlitShader);

    PBRShader *pbrShader = new PBRShader();
    pbrShader->init();
    registerShader("defaultLitPBR", pbrShader);

    OrthoGraphicShader *orthoGraphicShader = new OrthoGraphicShader();
    orthoGraphicShader->init();
    registerShader("orthoGraphic", orthoGraphicShader);

    SkyBoxShader *skyBoxShader = new SkyBoxShader();
    skyBoxShader->init();
    registerShader("skybox", skyBoxShader);

    EquirectangularShader *equirectangularShader = new EquirectangularShader();
    equirectangularShader->init();
    registerShader("equirectangularShader", equirectangularShader);

    IrradianceShader *irradianceShader = new IrradianceShader();
    irradianceShader->init();
    registerShader("irradianceShader", irradianceShader);

    PrefilterShader *prefilterShader = new PrefilterShader();
    prefilterShader->init();
    registerShader("prefilterShader", prefilterShader);

    BRDFShader *brdfShader = new BRDFShader();
    brdfShader->init();
    registerShader("brdfShader", brdfShader);

	ObjectOutlineShader *outlineShader = new ObjectOutlineShader();
	outlineShader->init();
	registerShader("outlineShader", outlineShader);
}

void ShaderManager::reloadProjectionMatrix(glm::mat4 projectionMatrix) {
    for(auto const& entry: shaders) {
        if(entry.second->isEnableProjectionMatrix()) {
            entry.second->start();
            entry.second->loadProjectionMatrix(projectionMatrix);
            entry.second->stop();
        }
    }
}

void ShaderManager::reloadViewMatrix(glm::mat4 viewMatrix) {
    for(auto const& entry: shaders) {
        if(entry.second->isEnableViewMatrix()) {
            entry.second->start();
            entry.second->loadViewMatrix(viewMatrix);
            entry.second->stop();
        }
    }
}

void ShaderManager::saveCamPos(glm::vec3 camPos) {
    for(auto & entry: shaders) {
        if(IShaderCamPos * p = dynamic_cast<IShaderCamPos *>(entry.second)) {
            entry.second->start();
            p->saveCamPos(camPos);
            entry.second->stop();
        }
    }
}

void ShaderManager::compileLights() {
    for(auto & lightShader: lightShaders) {
        lightShader->loadLights(RenderEngine::getInstance().getLights());
    }
}

void ShaderManager::registerShader(std::string name, Shader *shader) {
    shaders.insert(std::pair<std::string, Shader*>(name, shader));
    if(ILightShader * p = dynamic_cast<ILightShader *>(shader)) {
        lightShaders.push_back(p);
    }
}

Shader *ShaderManager::getShader(std::string name) {
    std::map<std::string, Shader*>::iterator it;
    it = shaders.find(name);
    if(it != shaders.end()) {
        return it->second;
    } else {
        std::cout << "Could not get shader " << name << std::endl;
        return nullptr;
    }
}


