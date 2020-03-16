//
// Created by Idrol on 02-10-2017.
//

#include "ReloadProjectionMatrix.h"
#include "../Shaders/ShaderManager.h"

ReloadProjectionMatrix::ReloadProjectionMatrix(glm::mat4 matrix) {
    this->matrix = matrix;
}

void ReloadProjectionMatrix::execute() {
    ShaderManager::reloadProjectionMatrix(matrix);
}
