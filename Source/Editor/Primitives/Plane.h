#pragma once

#include "Primitive.h"

class Plane: public Primitive {
public:
    Plane(PrimitivesUI *primitivesUI);
    Entity *createPrimitiveEntity() override;

private:
    int i = 0;
};


