#include "App.h"

App::App()
{
	mainwind = nullptr;
	mainrend = nullptr;

	background = nullptr;

	playerfield = nullptr;
	enemyfield = nullptr;

	
	
	
	running = true;
}

App::~App()
{
	if (background != nullptr) delete background;
	if (playerfield != nullptr) delete playerfield;
	if (enemyfield != nullptr) delete enemyfield;

}

// Инициализация библиотеки SDL2 и другие необходимые инициализации
void App::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw "SDL initialization failed";
	if ((mainwind = SDL_CreateWindow("Naval Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN)) == nullptr)
		throw "Can't create window";
	if ((mainrend = SDL_CreateRenderer(mainwind, -1, NULL)) == nullptr)
		throw "Can't create renderer";

	if ((background = new Sprite()) == nullptr)
		throw "Can't allocate memory for background sprite";
	background->loadTexture("images\\background.png\0", mainrend);
	background->setPosition(0, 0);
	background->setDimension(600, 800);

	if ((playerfield = new Field(mainrend)) == nullptr)
		throw "Can't allocate memory for player's field";
	if ((enemyfield = new Field(mainrend)) == nullptr)
		throw "Can't allocate memory for enemy's field";
}

// Удаление окна и рендера, закрытие соединения
void App::Close()
{
	SDL_DestroyRenderer(mainrend);
	SDL_DestroyWindow(mainwind);
	SDL_Quit();

	connection.Close();
}

void App::Rendering()
{

}

int App::Execution()
{
	Init();



	Close();
	return 1;
}