//
// Created by Idrol on 05-10-2017.
//

#include "RegisterTextureDefaults.h"
#include "../Texture/TextureManager.h"

void RegisterTextureDefaults::execute() {
    TextureManager::registerDefaults();
}
