#pragma once
#include "../Engine/Level/Level.h"

class ExampleLevel: public Level {
	void load() override;
	void createGunEntity();
	void createPBRSpheres();
	void update(float delta) override;
};