#pragma once
#include "yoshix_fix_function.h"

using namespace gfx;

struct SObject {
	BHandle* mesh;
	
	float position[3];
	float worldMatrix[16];

protected:
	void updateWorldMatrix();
};