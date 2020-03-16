//
// Created by Idrol on 02-10-2017.
//

#include "CompileLights.h"
#include "../Shaders/ShaderManager.h"

void CompileLights::execute() {
    ShaderManager::compileLights();
}
