#pragma once
#include "ball.h"
#include "gameData.h"
#include "menu.h"

#include <vector>

enum class EGameStatus {START, ON, PAUSED, SCORED, LEFTWON, RIGHTWON, GAMEOVER};

class CGame {
public:
	CGame(BHandle* ballMesh, BHandle* leftPaddleMesh, BHandle* rightPaddleMesh, BHandle* blockMesh);
	~CGame();

	std::vector<SObject*>* getObjects();
	void update(EKey key);

	CMenu* createMenu;

	void removeRightScore();		//public to release meshes when player closes game on his own
	void removeLeftScore();
	void removeMenu();
	bool showesMenu;

private:
	void handleCollision();
	void buildGame();
	void advanceGame(EKey key);

	void showMenu(EMenuTexture menuTexture);

	void showLeftScore(EMenuTexture menuTexture);
	void showRightScore(EMenuTexture menuTexture);

	bool isGoal();
	bool leftWon();
	bool rightWon();

private:
	EGameStatus gameStatus;
	EMenuTexture menuTexture;

	SBall ball;
	SPaddle paddles[NUM_OF_PADDLES];
	SBlock blocks[NUM_OF_BLOCKS];
	SBlock leftScore;
	SBlock rightScore;
	SBlock menu;

	std::vector<SObject*> objects;

	BHandle* ballMesh;
	BHandle* leftPaddleMesh;
	BHandle* rightPaddleMesh;
	BHandle* blockMesh;
	BHandle* menuMesh;
	BHandle* leftScoreMesh;
	BHandle* rightScoreMesh;

	int leftPlayerCounter;
	int rightPlayerCounter;
	bool isMultiPlayer;
	bool isEndless;
	bool firstBuild;
};