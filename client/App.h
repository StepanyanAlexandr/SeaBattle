#pragma once
#include "Connection.h"
#include "Field.h"

typedef enum GAMESTAGE
{
	PLACINGSHIPS = 0,
	GAME,
	ENDGAME
}GAMESTAGE;

class App
{
private:
	SDL_Window *mainwind;
	SDL_Renderer *mainrend;

	Connection connection;

	Sprite *background;
	Sprite *exitbutton;
	Sprite *playbutton;

	Sprite *playerturn;
	Sprite *enemyturn;
	Sprite *waiting;
	
	Ship *battleship;
	Ship *cruiser;
	Ship *submarine;
	Ship *boat;
	Ship *dragableship;

	Field *playerfield;
	Field *enemyfield;

	int battleshipnum;
	int cruisernum;
	int submarinenum;
	int boatnum;
	
	bool drag;
	bool running;
	bool turn;
	bool iswin;
	bool waitingenemy;

	GAMESTAGE stage;
public:
	App();
	~App();

	void Initialization();
	void MemoryAllocation();
	void Close();
	void Rendering();

	int Execution();
};