//
// Created by Idrol on 29-09-2017.
//

#include "Texture.h"

Texture::~Texture() {
    GLuint ids[1] {textureID};
    glDeleteTextures(1, ids);
}
