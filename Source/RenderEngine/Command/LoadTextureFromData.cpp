#include "LoadTextureFromData.h"
#include "../Texture/TextureLoader.h"

void LoadTextureFromData::execute() {
    TextureLoader::loadDataToTexture(texture, data, width, height, channels);
}
