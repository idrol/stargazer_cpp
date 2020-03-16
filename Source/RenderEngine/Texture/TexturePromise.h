#pragma once

class Texture;

class TexturePromise {
public:
    TexturePromise() {
    };

    void completePromise(Texture *texture) {
        completed = true;
        this->texture = texture;
    };
    Texture* getTexture() {
        return texture;
    };
    bool isCompleted() {
        return completed;
    }

private:
    bool completed = false;
    Texture *texture = nullptr;
};