//
// Created by Idrol on 05-10-2017.
//

#include "TextureLoader.h"
#include "Texture.h"
#include "../../Lib/stb_image.h"
#include "../Shaders/Shader.h"
#include "../Shaders/ShaderManager.h"
#include "../Shaders/EquirectangularShader.h"
#include "../Shaders/IrradianceShader.h"
#include "../Shaders/PrefilterShader.h"
#include "../Shaders/BRDFShader.h"
#include "../Model/Model.h"
#include "../Model/Mesh.h"
#include "../Material/EquirectangularMaterial.h"
#include "../Material/IrradianceMaterial.h"
#include "../Material/PrefilterMaterial.h"
#include "../Material/BRDFMaterial.h"
#include "../../Util/shape_util.h"
#include "../Window/WindowUtil.h"
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "../../ResourceManager/ResourceManager.h"
#include <algorithm>

GLuint TextureLoader::createTextureID() {
    GLuint texID;
    glGenTextures(1, &texID);
    return texID;
}

Texture *TextureLoader::getTexture(std::string path, GLenum target, GLenum dstPixel) {
    std::string finalPath = ResourceManager::getInstance().resolvePath(path);
    Texture *texture = new Texture(target, createTextureID(), path);
    glBindTexture(target, texture->getTextureID());
    int width, height, nrChannels;
    std::cout << "Loading texture " << finalPath << std::endl;
    unsigned char *data = stbi_load(finalPath.c_str(), &width, &height, &nrChannels, 4);
    std::cout << "Passed load line " << std::endl;
    int srcPixel = 0;
    if(nrChannels == 3) {
        srcPixel = GL_RGB;
    } else {
        srcPixel = GL_RGBA;
    }

    if(data) {
        glTexImage2D(target, 0, srcPixel, get2Fold(width), get2Fold(height), 0, dstPixel, GL_UNSIGNED_BYTE, data);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(target, GL_TEXTURE_LOD_BIAS, 0);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return texture;
    }
    std::cout << "Could not load texture" << std::endl;
    stbi_image_free(data);
    return nullptr;
}

unsigned char *TextureLoader::loadTextureData(std::string path, int &width, int &height, int &channels) {
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    return data;
}

void TextureLoader::loadDataToTexture(Texture *texture, unsigned char *data, int width, int height, int channels) {
    if(data) {
        texture->setTextureID(createTextureID());
        GLenum target = GL_TEXTURE_2D;
        glBindTexture(target, texture->getTextureID());
        int srcPixel = 0;
        if(channels == 3) {
            srcPixel = GL_RGB;
        } else {
            srcPixel = GL_RGBA;
        }


        glTexImage2D(target, 0, srcPixel, get2Fold(width), get2Fold(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(target, GL_TEXTURE_LOD_BIAS, 0);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Data invalid texture load failed" << std::endl;
    }

    stbi_image_free(data);
}

int TextureLoader::get2Fold(int fold) {
    int ret = 2;
    while(ret < fold) {
        ret *= 2;
    }
    return ret;
}

GLuint TextureLoader::loadCubeMap(std::vector<std::string> texture_files) {
    GLuint textureId = createTextureID();
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    unsigned int i = 0;
    for(auto & file: texture_files) {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
        if(data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0 , GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Could not load file " << file << std::endl;
        }
		stbi_image_free(data);
        i++;
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    return textureId;
}

Texture *TextureLoader::getHDRTexture(std::string path) {
    int width, height, nrComponents;
    std::string finalPath = ResourceManager::getInstance().resolvePath(path);
    float *data = stbi_loadf(finalPath.c_str(), &width, &height, &nrComponents, 0);
    if(data) {
        GLuint textureID = createTextureID();
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        Texture *texture = new Texture(GL_TEXTURE_2D, textureID, path);
        return texture;
    } else {
        return nullptr;
    }
}

Texture *TextureLoader::convertHDRTextureToCubeMap(Texture *texture, Model *cubeModel) {
    unsigned int captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

    unsigned int envCubeMap;
    envCubeMap = createTextureID();
    Texture *envCubeMapTexture = new Texture(GL_TEXTURE_CUBE_MAP, envCubeMap, "");
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubeMapTexture->getTextureID());
    for(unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] = {
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)),
    };

    EquirectangularShader *equirectangularShader = (EquirectangularShader*) ShaderManager::getShader("equirectangularShader");
    equirectangularShader->start();
    equirectangularShader->loadInt("equirectangularMap", 0);
    equirectangularShader->loadProjectionMatrix(captureProjection);

    EquirectangularMaterial *material = new EquirectangularMaterial();
    material->setEquirectangularTexture(texture);
    cubeModel->setMaterial(material);
    cubeModel->disableCullFace();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 512, 512);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for(unsigned int i = 0; i < 6; ++i) {
        equirectangularShader->start();
        equirectangularShader->loadViewMatrix(captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubeMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeModel->draw();
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubeMap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	WindowUtil::setDefaultGLViewport();
    glDeleteFramebuffers(1, &captureFBO);
    glDeleteRenderbuffers(1, &captureRBO);
    return envCubeMapTexture;
}

Texture *TextureLoader::generateIrradianceMapFromCubeMap(Texture *texture, Model *cubeModel) {
    unsigned int irradianceMap = createTextureID();
    Texture *irradianceTexture = new Texture(GL_TEXTURE_CUBE_MAP, irradianceMap, "");
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for(unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned int captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] = {
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)),
    };

    IrradianceShader *irradianceShader = (IrradianceShader*) ShaderManager::getShader("irradianceShader");
    irradianceShader->start();
    irradianceShader->loadProjectionMatrix(captureProjection);

    IrradianceMaterial *material = new IrradianceMaterial();
    material->setEnviormentMap(texture);

    cubeModel->setMaterial(material);
    cubeModel->disableCullFace();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 32, 32);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for(unsigned int i = 0; i < 6; ++i) {
        irradianceShader->start();
        irradianceShader->loadViewMatrix(captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeModel->draw();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    WindowUtil::setDefaultGLViewport();
    glDeleteFramebuffers(1, &captureFBO);
    glDeleteRenderbuffers(1, &captureRBO);

    return irradianceTexture;
}

Texture *TextureLoader::prefilterCubeMap(Texture *texture, Model *cubeModel) {
    unsigned int prefilterMap = createTextureID();
    Texture *prefilterTexture = new Texture(GL_TEXTURE_CUBE_MAP, prefilterMap, "");
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for(unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] = {
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)),
            glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)),
    };

    unsigned int captureFBO, captureRBO;

    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    PrefilterShader *prefilterShader = (PrefilterShader*) ShaderManager::getShader("prefilterShader");
    prefilterShader->start();
    prefilterShader->loadProjectionMatrix(captureProjection);

    PrefilterMaterial *material = new PrefilterMaterial();
    material->setEnviormentMap(texture);
    cubeModel->setMaterial(material);
    cubeModel->disableCullFace();

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    unsigned int maxMipLevels = 5;
    for(unsigned int mip = 0; mip < maxMipLevels; ++mip) {
        unsigned int mipWidth = (unsigned int)(128 * std::pow(0.5, mip));
        unsigned int mipHeight = (unsigned int)(128 * std::pow(0.5, mip));
        glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        material->setRoughness(roughness);
        for(unsigned int i = 0; i < 6; ++i) {
            prefilterShader->start();
            prefilterShader->loadViewMatrix(captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            cubeModel->draw();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &captureFBO);
    glDeleteRenderbuffers(1, &captureRBO);

    WindowUtil::setDefaultGLViewport();

    return prefilterTexture;
}

Texture *TextureLoader::generateBRDFLut(Model *quadModel) {
    unsigned int brdfLUTTexture = createTextureID();
    Texture *brdfTexture = new Texture(GL_TEXTURE_2D, brdfLUTTexture, "");
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned int captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    BRDFMaterial *material = new BRDFMaterial();

    quadModel->setMaterial(material);
    quadModel->disableCullFace();

    BRDFShader *brdfShader = (BRDFShader*) ShaderManager::getShader("brdfShader");

    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureView = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));
    quadModel->setPosition(glm::vec3(0, 0, -1));

    glViewport(0, 0, 512, 512);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    brdfShader->start();
    quadModel->draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &captureFBO);
    glDeleteRenderbuffers(1, &captureRBO);

    WindowUtil::setDefaultGLViewport();

    return brdfTexture;
}
