//
// Created by Idrol on 12-10-2017.
//

#include "SetBRDFLUT.h"
#include "../Texture/TextureManager.h"

SetBRDFLUT::SetBRDFLUT(std::string name) {
    this->name = name;
}

void SetBRDFLUT::execute() {
    TextureManager::setBRDFLUT(name);
}
