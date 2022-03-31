#pragma once
#include "object.h"


struct SBlock : SObject{
public:
	SBlock();
	SBlock(BHandle* blockMesh, float position[3]);
	
};

BHandle CreateBlockMesh(BHandle texture, float width, float height, float depth);