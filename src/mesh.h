#pragma once
#include "yoshix_fix_function.h"

using namespace gfx;

BHandle CreateMesh(int numberOfVertices, float* vertices, int numberOfIndices, int* indices, float* texCoords, BHandle texture);