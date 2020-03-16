#pragma once

#include "Primitive.h"

class Cube: public Primitive {
public:
    Cube(PrimitivesUI *primitivesUI);
    Entity *createPrimitiveEntity() override;

private:
    int i = 0;
};


