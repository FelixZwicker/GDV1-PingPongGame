#pragma once
#include "yoshix_fix_function.h"
#include "block.h"
using namespace gfx;

enum class EMenuTexture { START, PAUSE, GOAL, BLUEWON, REDWON, SCOREZERO, SCOREONE, SCORETWO, SCORETHREE, MENU, LEFTSCORE, RIGHTSCORE };

class CMenu {
public:
	CMenu();
	~CMenu();

	BHandle* createMenuMesh(EMenuTexture menuTexture);
	BHandle* createScoreMesh(EMenuTexture menuTexture, bool player); //false == left player, true== right player
	void releaseMesh(EMenuTexture menuTexture);

private:
	BHandle startMenuTexture;
	BHandle pauseMenuTexture;
	BHandle goalMenuTexture;
	BHandle blueWonMenuTexture;
	BHandle redWonMenuTexture;
	BHandle menuMesh;

	BHandle scoreZeroTexture;
	BHandle scoreOneTexture;
	BHandle scoreTwoTexture;
	BHandle scoreThreeTexture;
	BHandle leftScoreMesh;
	BHandle rightScoreMesh;

	float startMenuSize[3];
	float menuSize[3];
	float scoreSize[3];
};