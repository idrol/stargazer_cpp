//
// Created by Idrol on 02-10-2017.
//

#include "LoadTexture.h"
#include "../Texture/TextureManager.h"

LoadTexture::LoadTexture(std::string loc) {
    this->loc = loc;
}

void LoadTexture::execute() {
    TextureManager::registerTextureWithPath(loc);
}


