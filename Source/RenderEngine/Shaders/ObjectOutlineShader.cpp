#include "ObjectOutlineShader.h"

void ObjectOutlineShader::bindAttributes() {
	bindAttribute(0, "position");
	bindAttribute(1, "uv");
	bindAttribute(2, "normal");
}