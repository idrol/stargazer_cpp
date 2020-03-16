#pragma once

#include "Primitive.h"

class Player: public Primitive {
public:
    Player(PrimitivesUI *primitivesUI);
    Entity *createPrimitiveEntity() override;
};


