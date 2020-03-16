#pragma once

class PrimitivesUI;
class Entity;
class PhysicsComponent;
class Texture;

class Primitive {
public:
	Primitive(PrimitivesUI *primitivesUI, Texture *iconTexture) {
		this->primitivesUI = primitivesUI;
		this->iconTexture = iconTexture;
	};

	virtual Entity *createPrimitiveEntity() {return nullptr;};
	virtual Texture *getPrimitiveIcon() {return iconTexture;};

private:
	PrimitivesUI *primitivesUI;
	Texture *iconTexture;
};