#pragma once
#include "Shader.h"

class ObjectOutlineShader: public Shader {
public:
	ObjectOutlineShader(): Shader("Engine/shaders/generic/objectOutline.shader") {};
	void bindAttributes() override;
};