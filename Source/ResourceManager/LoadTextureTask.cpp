#include "LoadTextureTask.h"
#include "../RenderEngine/Texture/Texture.h"
#include "../RenderEngine/Texture/TextureLoader.h"
#include "../RenderEngine/RenderEngine.h"
#include "../RenderEngine/Command/LoadTextureFromData.h"

void LoadTextureTask::loadResource() {
    int width, height, channels;
    unsigned char *data = TextureLoader::loadTextureData(path, width, height, channels);
    RenderEngine::getInstance().addCommand(new LoadTextureFromData(texture, data, width, height, channels));
}
