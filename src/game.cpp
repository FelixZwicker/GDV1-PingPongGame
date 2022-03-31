#include "game.h"
#include <iostream>

CGame::CGame(BHandle* ballMesh, BHandle* leftPaddleMesh, BHandle* rightPaddleMesh, BHandle* blockMesh)
	: gameStatus(EGameStatus::START)
	, menuTexture(EMenuTexture::START)
	, createMenu(nullptr)

	, ballMesh(ballMesh)
	, leftPaddleMesh(leftPaddleMesh)
	, rightPaddleMesh(rightPaddleMesh)
	, blockMesh(blockMesh)
	, menuMesh(nullptr)
	, leftScoreMesh(nullptr)
	, rightScoreMesh(nullptr)

	, leftPlayerCounter(0)
	, rightPlayerCounter(0)
	, isEndless(false)
	, isMultiPlayer(true)
	, showesMenu(false)
	, firstBuild(true)
{
	this->createMenu = new CMenu();
	this->buildGame();
}

CGame::~CGame() {
	this->objects.clear();
}

std::vector<SObject*>* CGame::getObjects() {
	return &objects;
}

void CGame::update(EKey key) {
	switch (this->gameStatus) {
	case EGameStatus::START:
		this->showMenu(EMenuTexture::START);
		this->firstBuild = false;

		if (key == EKey::ONE) {					//activates SinglePlayer
			isMultiPlayer = false;
			std::cout << "SINGLEPLAYER ACTIVATED\n";
		}

		if (key == EKey::TWO) {					//activates Endless-Mode
			isEndless = true;
			std::cout << "ENDLESS ACTIVATED\n";
		}

		if (key == EKey::SPACE) {				//starts game on default settings
			this->removeMenu();
			this->gameStatus = EGameStatus::ON;
		}
		break;

	case EGameStatus::ON:
		this->advanceGame(key);					//controlles movement and collisions

		if (key == EKey::SPACE) {				
			this->gameStatus = EGameStatus::PAUSED;
		}

		if (this->isGoal()) {					
			this->gameStatus = EGameStatus::SCORED;
		}
		break;

	case EGameStatus::PAUSED:
		this->showMenu(EMenuTexture::PAUSE);

		if (key == EKey::SPACE) {
			this->removeMenu();
			this->gameStatus = EGameStatus::ON;
		}
		break;

	case EGameStatus::SCORED:
		if (this->leftWon()) {					//left scored 3 times
			this->leftPlayerCounter = 0;
			this->rightPlayerCounter = 0;
			this->gameStatus = EGameStatus::LEFTWON;
		}
		else if (this->rightWon()) {			//right scored 3 times
			this->leftPlayerCounter = 0;
			this->rightPlayerCounter = 0;
			this->gameStatus = EGameStatus::RIGHTWON;
		}
		else {									//goal
			this->showMenu(EMenuTexture::GOAL);

			if (key == EKey::SPACE) {
				this->removeMenu();
				this->buildGame();
				this->gameStatus = EGameStatus::ON;
			}
		}
		break;

	case EGameStatus::LEFTWON:
		this->showMenu(EMenuTexture::BLUEWON);

		if (!isEndless) {						//no endless mode
			this->gameStatus = EGameStatus::GAMEOVER;
		}
		else if (key == EKey::SPACE) {
			this->removeMenu();
			this->buildGame();
			this->gameStatus = EGameStatus::ON;
		}
		break;

	case EGameStatus::RIGHTWON:
		this->showMenu(EMenuTexture::REDWON);

		if (!isEndless) {					//no Endless-Mode
			this->gameStatus = EGameStatus::GAMEOVER;
		}
		if (key == EKey::SPACE) {
			this->removeMenu();
			this->buildGame();
			this->gameStatus = EGameStatus::ON;
		}
		break;

	case EGameStatus::GAMEOVER:
		if (key == EKey::SPACE) {			//stops Application
			if (showesMenu) {
				removeMenu();
			}
			createMenu->~CMenu();			// releases textures
			removeLeftScore();
			removeRightScore();
			StopApplication();
		}
	}
}

void CGame::advanceGame(EKey key) {
	this->paddles[0].move(key, BORDER_TOP, BORDER_BOTTOM, isMultiPlayer);	//left paddle, bool controls changes from UP/DOWN arrows to W/S controls
	this->paddles[1].move(key, BORDER_TOP, BORDER_BOTTOM, false);			//right paddle
	this->handleCollision();
	this->ball.move();
}

void CGame::handleCollision() {
	this->ball.handleCollision(BORDER_TOP, BORDER_BOTTOM);
	this->ball.handleCollision(this->paddles[0]);		//with left paddle
	this->ball.handleCollision(this->paddles[1]);		//with right paddle
}

void CGame::buildGame() {					//puts needed game objects in vector
	this->objects.clear();					//clears vector befor rebuild

	this->ball = SBall(ballMesh);
	this->objects.push_back(&this->ball);

	this->paddles[0] = SPaddle(leftPaddleMesh, PADDELS[0].position);
	this->objects.push_back(&this->paddles[0]);

	this->paddles[1] = SPaddle(rightPaddleMesh, PADDELS[1].position);
	this->objects.push_back(&this->paddles[1]);

	for (int i = 0; i < NUM_OF_BLOCKS; i++) {
		this->blocks[i] = SBlock(blockMesh, BORDER_BLOCKS[i].position);
		this->objects.push_back(&this->blocks[i]);
	}

	if (!firstBuild) {					//release old mesh in rebuild
		removeRightScore();
		removeLeftScore();
	}

	switch (rightPlayerCounter) {			//scoreMesh depends on goals
	case 0:
		showRightScore(EMenuTexture::SCOREZERO);
		break;
	case 1:
		showRightScore(EMenuTexture::SCOREONE);
		break;
	case 2:
		showRightScore(EMenuTexture::SCORETWO);
		break;
	case 3:
		showRightScore(EMenuTexture::SCORETHREE);
		break;
	}

	switch (leftPlayerCounter) {
	case 0:
		showLeftScore(EMenuTexture::SCOREZERO);
		break;
	case 1:
		showLeftScore(EMenuTexture::SCOREONE);
		break;
	case 2:
		showLeftScore(EMenuTexture::SCORETWO);
		break;
	case 3:
		showLeftScore(EMenuTexture::SCORETHREE);
		break;
	}
}

void CGame::showMenu(EMenuTexture menuTexture) {	//creates menu mesh with needes texture
	if (!showesMenu) {	
		this->menuMesh = createMenu->createMenuMesh(menuTexture);
		this->menu = SBlock(this->menuMesh, MENU[0].position);
		this->objects.push_back(&this->menu);
		showesMenu = true;
	}
}

void CGame::removeMenu() {
	this->objects.pop_back();
	this->createMenu->releaseMesh(EMenuTexture::MENU);
	showesMenu = false;
}

void CGame::showLeftScore(EMenuTexture menuTexture) {	//score mesh with needed texture
	this->leftScoreMesh = createMenu->createScoreMesh(menuTexture, false);
	this->leftScore = SBlock(this->leftScoreMesh, SCORE[0].position);
	this->objects.push_back(&this->leftScore);
}

void CGame::removeLeftScore() {		//frees mesh space
	this->createMenu->releaseMesh(EMenuTexture::LEFTSCORE);
}

void CGame::showRightScore(EMenuTexture menuTexture) {
	this->rightScoreMesh = createMenu->createScoreMesh(menuTexture, true);
	this->rightScore = SBlock(rightScoreMesh, SCORE[1].position);
	this->objects.push_back(&this->rightScore);
}

void CGame::removeRightScore() {
	this->createMenu->releaseMesh(EMenuTexture::RIGHTSCORE);
}

bool CGame::isGoal() {
	if (ball.isOutLeft(BORDER_LEFT) == true) {
		rightPlayerCounter++;
		return true;
	}

	if (ball.isOutRight(BORDER_RIGHT) == true) {
		leftPlayerCounter++;
		return true;
	}

	return false;
}

bool CGame::leftWon() {
	if (leftPlayerCounter == 3) {
		return true;
	}

	return false;
}

bool CGame::rightWon() {
	if (rightPlayerCounter == 3) {
		return true;
	}

	return false;
}