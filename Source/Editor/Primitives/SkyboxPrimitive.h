#pragma once

#include "Primitive.h"

class SkyboxPrimitive: public Primitive {
public:
    SkyboxPrimitive(PrimitivesUI *primitivesUI);
    Entity *createPrimitiveEntity() override;
};
