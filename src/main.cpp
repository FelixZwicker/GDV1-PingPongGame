#include "app.h"
#include <iostream>

using namespace std;

void main() {
	cout << "<--------------------PING PONG - NEON EVOLUTION-------------------------->\n";
	cout << endl << endl << endl;
	cout << "Game: \n\n";
	cout << "	This game is a basic Ping-Pong type of game\n";
	cout << "	and ment to be played in fullscreen\n";
	cout << "	The goal is to beat your opponent and score 3 times\n";
	cout << endl;
	cout << "Controles:	\n\n";
	cout << "	Press '1' in the beginning to select SinglePlayer\n";
	cout << "	Controls are only UP/DOWN - ARROWS in SinglePlayer\n";
	cout << endl;
	cout << "	Press '2' in the beginning to select Endless-Mode\n";
	cout << endl;
	cout << "	Continue with 'Space' for Multiplayer and no Endless-Mode\n";
	cout << endl << endl;
	cout << "	Have a lot of fun and THANKS for playing\n";
	cout << endl;
	cout << "<------------------------------------------------------------------------>\n";

	CApplication app;

	RunApplication(1280, 720, "Ping Pong - Neon Evoultion", &app);
}