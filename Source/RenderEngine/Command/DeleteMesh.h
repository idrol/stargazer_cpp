#pragma once
#include "Command.h"

class Mesh;

class DeleteMesh: public Command {
public:
    explicit DeleteMesh(Mesh *mesh);
    void execute() override;
private:
    Mesh *mesh;
};
