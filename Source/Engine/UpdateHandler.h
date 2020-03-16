#pragma once

class EntityManager;

class UpdateHandler
{
public:
	UpdateHandler();
	~UpdateHandler() {};
	void initialize();
	void loop(float delta);
	void run();
	void stop();
private:
	bool togglePressed = false;
	EntityManager *entityManager;
};

