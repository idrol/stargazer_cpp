//
// Created by Idrol on 02-10-2017.
//

#include "ReloadViewMatrix.h"
#include "../Shaders/ShaderManager.h"

ReloadViewMatrix::ReloadViewMatrix(glm::mat4 matrix) {
    this->matrix = matrix;
}

void ReloadViewMatrix::execute() {
    ShaderManager::reloadViewMatrix(matrix);
}
