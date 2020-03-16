#pragma once

#include <GLM/glm.hpp>

class Camera {
public:
	Camera(float fov, float near, float far);
    float getSensitivity();
    double getMouseX();
    double getMouseY();
    void setPitch(float pitch);
    void setYaw(float yaw);
    void setRoll(float roll);
    void setPosition(glm::vec3 position);
    void update();
	void reload();
    glm::vec3 getPosition();
    float getPitch();
    float getYaw();
    float getRoll();
	float getFov() {
		return fov;
	};
	float getNear() {
		return near;
	};
	float getFar() {
		return far;
	};

protected:
    glm::vec3 position = glm::vec3(0,0,0);

private:
    float pitch = 0, yaw = 0, roll = 0;
    double mouseX = 0, mouseY = 0;
    float sensitivity = 0.2f;
	float fov = 70, near = 1, far = 10;
};
