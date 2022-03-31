#include "paddle.h"

const float SPEED = 0.1f;

SPaddle::SPaddle(){}

SPaddle::SPaddle(BHandle* paddleMesh, float position[3]) {
	this->mesh = paddleMesh;
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];

	this->speed = SPEED;

	this->updateWorldMatrix();
}

void SPaddle::move(EKey key, float upperLimit, float lowerLimit, bool controls) {
	float newY = this->position[1];
	float halfHeight = 1.5f / 2 + 0.5f;			//paddle height / 2 + half block edge length
	if (!controls) {
		switch (key) {
		case EKey::UP:
			newY += this->speed;
			if (newY + halfHeight < upperLimit) {
				this->position[1] = newY;
				this->updateWorldMatrix();
			}
			break;
		case EKey::DOWN:
			newY -= this->speed;
			if (newY - halfHeight > lowerLimit) {
				this->position[1] = newY;
				this->updateWorldMatrix();
			}
			break;
		}
	}
	else {
		switch (key) {
		case EKey::W:
			newY += this->speed;
			if (newY + halfHeight < upperLimit) {
				this->position[1] = newY;
				this->updateWorldMatrix();
			}
			break;
		case EKey::S:
			newY -= this->speed;
			if (newY - halfHeight > lowerLimit) {
				this->position[1] = newY;
				this->updateWorldMatrix();
			}
			break;
		}
	}
}