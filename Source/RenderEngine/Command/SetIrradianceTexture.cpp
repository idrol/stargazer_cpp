//
// Created by Idrol on 12-10-2017.
//

#include "SetIrradianceTexture.h"
#include "../Texture/TextureManager.h"

SetIrradianceTexture::SetIrradianceTexture(std::string name) {
    this->name = name;
}

void SetIrradianceTexture::execute() {
    TextureManager::setIrradianceTexture(name);
}
