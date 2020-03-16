#pragma once

#include <GLM/glm.hpp>

class Light {
public:
    Light(glm::vec3 position, glm::vec3 color, int intensity){
        this->position = position;
        this->color = color;
		this->intensity = intensity;
    };

    glm::vec3 getPosition() {return position;};
    void setPosition(glm::vec3 position) {this->position = position;};
    glm::vec3 getColor() {return color;};
    void setColor(glm::vec3 color) {this->color = color;};
	int getIntensity() {return intensity;};
	void setIntensity(int intensity) {this->intensity = intensity;};

private:
    glm::vec3 position, color;
	int intensity;
};