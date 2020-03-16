#pragma once

#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture(GLenum target, GLuint textureID, std::string path) {
        this->target = target;
        this->textureID = textureID;
        this->path = path;
    }

    ~Texture();

    void setHeight(int height) {
        this->height;
        setHeight();
    }

    void setWidth(int width) {
        this->width;
        setWidth();
    }

    int getImageHeight() { return height;};
    int getImageWidth() { return width;};
    float getHeight() { return heightRatio;};
    float getWidth() { return widthRatio;};
    void setTextureHeight(int texHeight) {
        this->texHeight = texHeight;
        setHeight();
    };

    void setTextureWidth(int texWidth) {
        this->texWidth = texWidth;
        setWidth();
    };

    void setHeight() {
        if(texHeight != 0) {
            heightRatio = (float)height/(float)texHeight;
        }
    };

    void setWidth() {
        if(texWidth != 0) {
            widthRatio = (float)width/(float)texWidth;
        }
    };

    GLuint getTextureID() { return textureID;};
    void setTextureID(GLuint id) {this->textureID = id;};
    GLenum getTarget() { return target;};
    std::string getPath() {
        return path;
    };
    void setPath(std::string path) {
        this->path = path;
    }

private:
    GLenum target;
    GLuint textureID;
    int height;
    int width;
    int texWidth;
    int texHeight;
    float widthRatio;
    float heightRatio;
    std::string path;
};
