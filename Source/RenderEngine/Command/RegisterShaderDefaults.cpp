#include "RegisterShaderDefaults.h"
#include "../Shaders/ShaderManager.h"

void RegisterShaderDefaults::execute() {
    ShaderManager::registerDefaults();
}
