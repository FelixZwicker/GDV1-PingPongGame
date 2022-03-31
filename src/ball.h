#pragma once
#include "paddle.h"


struct SBall : SObject{
public:
	SBall();
	SBall(BHandle* ballMesh);

	bool handleCollision(float topBoarder, float bottomBoarder);
	bool handleCollision(SPaddle& paddle);

	bool hitCheckpoint(int hits);

	bool isOutLeft(float boarder);
	bool isOutRight(float boarder);

	void move();

private:
	float speed;
	float direction[3];
	int hits;

	//Collisions
	enum class ECollisionAt {TOP, BOTTOM, LEFT, RIGHT};
	void changeDirection(ECollisionAt collisionAt);
};

BHandle CreateBallMesh(BHandle texture, float _Radius);