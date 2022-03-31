#include "menu.h"

const float STARTMENUSIZE[] =	{ 8.0f, 4.0f, 1.0f }; //width, height, depth
const float MENUSIZE[] =		{ 4.0f, 2.0f, 1.0f };
const float SCORESIZE[] =		{ 2.0f, 1.0f, 1.0f };

CMenu::CMenu() {
	CreateTexture("..\\data\\images\\start_menu.jpg", &startMenuTexture);
	CreateTexture("..\\data\\images\\pause_menu.jpg", &pauseMenuTexture);
	CreateTexture("..\\data\\images\\goal_menu.jpg", &goalMenuTexture);
	CreateTexture("..\\data\\images\\blue_won.jpg", &blueWonMenuTexture);
	CreateTexture("..\\data\\images\\red_won.jpg", &redWonMenuTexture);

	CreateTexture("..\\data\\images\\score_0.jpg", &scoreZeroTexture);
	CreateTexture("..\\data\\images\\score_1.jpg", &scoreOneTexture);
	CreateTexture("..\\data\\images\\score_2.jpg", &scoreTwoTexture);
	CreateTexture("..\\data\\images\\score_3.jpg", &scoreThreeTexture);


	startMenuSize[0] = STARTMENUSIZE[0];
	startMenuSize[1] = STARTMENUSIZE[1];
	startMenuSize[2] = STARTMENUSIZE[2];

	menuSize[0] = MENUSIZE[0];
	menuSize[1] = MENUSIZE[1];
	menuSize[2] = MENUSIZE[2];

	scoreSize[0] = SCORESIZE[0];
	scoreSize[1] = SCORESIZE[1];
	scoreSize[2] = SCORESIZE[2];
}

CMenu::~CMenu() {
	//Menu
	ReleaseTexture(startMenuTexture);
	ReleaseTexture(pauseMenuTexture);
	ReleaseTexture(goalMenuTexture);
	ReleaseTexture(blueWonMenuTexture);
	ReleaseTexture(redWonMenuTexture);
	//Score
	ReleaseTexture(scoreZeroTexture);
	ReleaseTexture(scoreOneTexture);
	ReleaseTexture(scoreTwoTexture);
	ReleaseTexture(scoreThreeTexture);
};

BHandle* CMenu::createMenuMesh(EMenuTexture menuTexture) {
	switch (menuTexture) {
	case EMenuTexture::START:
		this->menuMesh = CreateBlockMesh(startMenuTexture, startMenuSize[0], startMenuSize[1], startMenuSize[2]);
		break;
	case EMenuTexture::PAUSE:
		this->menuMesh = CreateBlockMesh(pauseMenuTexture, menuSize[0], menuSize[1], menuSize[2]);
		break;
	case EMenuTexture::GOAL:
		this->menuMesh = CreateBlockMesh(goalMenuTexture, menuSize[0], menuSize[1], menuSize[2]);
		break;
	case EMenuTexture::BLUEWON:
		this->menuMesh = CreateBlockMesh(blueWonMenuTexture, menuSize[0], menuSize[1], menuSize[2]);
		break;
	case EMenuTexture::REDWON:
		this->menuMesh = CreateBlockMesh(redWonMenuTexture, menuSize[0], menuSize[1], menuSize[2]);
		break;
	}

	return &menuMesh;
}

BHandle* CMenu::createScoreMesh(EMenuTexture menuTexture, bool player) {
	if (player) {
		switch (menuTexture) {
		case EMenuTexture::SCOREZERO:
			this->rightScoreMesh = CreateBlockMesh(scoreZeroTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		case EMenuTexture::SCOREONE:
			this->rightScoreMesh = CreateBlockMesh(scoreOneTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		case EMenuTexture::SCORETWO:
			this->rightScoreMesh = CreateBlockMesh(scoreTwoTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		case EMenuTexture::SCORETHREE:
			this->rightScoreMesh = CreateBlockMesh(scoreThreeTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		}
		return &rightScoreMesh;
	}
	else if (!player) {
		switch (menuTexture) {
		case EMenuTexture::SCOREZERO:
			this->leftScoreMesh = CreateBlockMesh(scoreZeroTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		case EMenuTexture::SCOREONE:
			this->leftScoreMesh = CreateBlockMesh(scoreOneTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		case EMenuTexture::SCORETWO:
			this->leftScoreMesh = CreateBlockMesh(scoreTwoTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		case EMenuTexture::SCORETHREE:
			this->leftScoreMesh = CreateBlockMesh(scoreThreeTexture, scoreSize[0], scoreSize[1], scoreSize[2]);
			break;
		}
		return &leftScoreMesh;
	}
}

void CMenu::releaseMesh(EMenuTexture menuTexture) {
	switch (menuTexture) {
	case EMenuTexture::MENU:
		ReleaseMesh(menuMesh);
		break;
	case EMenuTexture::LEFTSCORE:
		ReleaseMesh(leftScoreMesh);
		break;
	case EMenuTexture::RIGHTSCORE:
		ReleaseMesh(rightScoreMesh);
		break;
	}
}