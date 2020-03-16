#pragma once

#include "Command.h"

class Texture;

class LoadTextureFromData: public Command {
public:
    LoadTextureFromData(Texture *texture, unsigned char *data, int width, int height, int channels) {
        this->texture = texture;
        this->data = data;
        this->width = width;
        this->height = height;
        this->channels = channels;
    };
    void execute() override;

private:
    Texture *texture = nullptr;
    unsigned char *data;
    int width, height, channels;
};
