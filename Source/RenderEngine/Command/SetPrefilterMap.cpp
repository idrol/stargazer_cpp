//
// Created by Idrol on 12-10-2017.
//

#include "SetPrefilterMap.h"
#include "../Texture/TextureManager.h"

SetPrefilterMap::SetPrefilterMap(std::string name) {
    this->name = name;
}

void SetPrefilterMap::execute() {
    TextureManager::setPrefilterMap(name);
}
