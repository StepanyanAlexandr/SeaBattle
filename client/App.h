#pragma once
#include <SDL.h>
#include "Connection.h"
#include "Field.h"

class App
{
private:
	SDL_Window *mainwind;
	SDL_Renderer *mainrend;

	Connection connection;

	Sprite *background;
	Sprite *exitbutton;
	
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
public:
	App();
	~App();

	void Initialization();
	void MemoryAllocation();
	void Close();
	void Rendering();

	int Execution();
};