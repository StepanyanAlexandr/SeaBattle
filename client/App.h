#pragma once
#include <SDL.h>
#include "Connection.h"
#include "Field.h"
//#include "Ship.h"

class App
{
private:
	SDL_Window *mainwind;
	SDL_Renderer *mainrend;

	Connection connection;

	Sprite *background;

	Field *playerfield;
	Field *enemyfield;

	bool running;
public:
	App();
	~App();

	void Init();
	void Close();
	void Rendering();

	int Execution();
};