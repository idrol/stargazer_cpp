#include "Material.h"
#include "../Shaders/Shader.h"

Material::Material(std::string type, Shader *shader) {
    this->shader = shader;
    this->type = type;
}

void Material::apply() {
    bindTextures();
    shader->start();
    setShaderProperties();
}
