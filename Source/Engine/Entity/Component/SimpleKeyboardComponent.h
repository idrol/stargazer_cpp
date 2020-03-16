#pragma once
#include "Component.h"

class SimpleKeyboardComponent: public Component {
public:
	SimpleKeyboardComponent(Entity *entity): Component(entity, "SimpleKeyboardComponent", "SimpleKeyboardComponent") {};
	void update(float delta) override;
	void setSpeed(float speed) {
		this->speed = speed;
	};
	float getSpeed() {
		return speed;
	};
	float speed = 4;
};