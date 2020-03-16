#pragma once
#include "Primitive.h"

class LightPrimitive: public Primitive {
public:
	LightPrimitive(PrimitivesUI *primitivesUI);
	Entity *createPrimitiveEntity() override;

private:
	int i = 0;
};