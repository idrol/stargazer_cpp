//
// Created by Idrol on 12-10-2017.
//

#include "BRDFMaterial.h"
#include "../Shaders/ShaderManager.h"
#include "../Shaders/Shader.h"

BRDFMaterial::BRDFMaterial(): Material("BRDFMaterial", ShaderManager::getShader("brdfShader")) {

}