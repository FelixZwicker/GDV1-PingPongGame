#pragma once
#include "key.h"
#include "object.h"


struct SPaddle : SObject{
public:
	SPaddle();
	SPaddle(BHandle* paddleMesh, float position[3]);

	void move(EKey key, float upperLimit, float lowerLimit, bool controls); //true == W'S, false == UP'DOWN

private:
	float speed;
};