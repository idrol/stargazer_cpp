#pragma once

class Camera;

class EditorCamera {
public:
    EditorCamera(Camera *camera) {
        this->camera = camera;
    };
    void update(float delta);
    Camera *getCamera();
    float getSpeed() {
        return speed;
    };
    void setSpeed(float speed) {
        this->speed = speed;
    };

private:
    Camera *camera;
    float speed = 4;
};


