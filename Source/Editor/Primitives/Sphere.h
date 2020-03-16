#pragma once
#include "Primitive.h"


class Sphere: public Primitive {
public:
	Sphere(PrimitivesUI *primitivesUI);
	Entity *createPrimitiveEntity() override;

private:
	int i = 0;
};