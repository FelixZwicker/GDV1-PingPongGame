#include "object.h"

void SObject::updateWorldMatrix() {
	GetTranslationMatrix(this->position[0], this->position[1], this->position[2], this->worldMatrix);
}