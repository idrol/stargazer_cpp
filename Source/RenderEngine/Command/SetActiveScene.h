#pragma once

#include "Command.h"

class Scene;

class SetActiveScene: public Command {
public:
    SetActiveScene(Scene *scene);
    void execute() override;

private:
    Scene *scene;
};