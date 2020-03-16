#pragma once
#include "Command.h"

class Mesh;

class CreateMesh: public Command
{
	Mesh *mesh;
public:
	explicit CreateMesh(Mesh *mesh);
	void execute() override;
	~CreateMesh();
};

