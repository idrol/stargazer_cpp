//
// Created by Idrol on 12-10-2017.
//

#include "GenerateBRDFLUT.h"
#include "../Texture/TextureManager.h"
#include "../Texture/TextureLoader.h"

GenerateBRDFLUT::GenerateBRDFLUT(std::string name, Model *quadModel) {
    this->name = name;
    this->quadModel = quadModel;
}

void GenerateBRDFLUT::execute() {
    TextureManager::registerTextureWithName(name, TextureLoader::generateBRDFLut(quadModel));
}
