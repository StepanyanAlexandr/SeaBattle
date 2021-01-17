#include "App.h"

App::App()
{
	mainwind = nullptr;
	mainrend = nullptr;

	background = nullptr;
	exitbutton = nullptr;

	battleship = nullptr;
	cruiser = nullptr;
	submarine = nullptr;
	boat = nullptr;
	dragableship = nullptr;

	playerfield = nullptr;
	enemyfield = nullptr;

	boatnum = 0;
	submarinenum = 0;
	cruisernum = 0;
	battleshipnum = 0;
	
	drag = false;
	running = true;
}

App::~App()
{
	if (background != nullptr) delete background;
	if (exitbutton != nullptr) delete exitbutton;
	if (playerfield != nullptr) delete playerfield;
	if (enemyfield != nullptr) delete enemyfield;
	if (battleship != nullptr) delete battleship;
	if (cruiser != nullptr) delete cruiser;
	if (submarine != nullptr) delete submarine;
	if (boat != nullptr) delete boat;
	if (dragableship != nullptr) delete dragableship;

	Close();
}

// Инициализация библиотеки SDL2 и другие необходимые инициализации
void App::Initialization()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw "SDL initialization failed";
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw "SDL_image initialization fault";
	if ((mainwind = SDL_CreateWindow("Naval Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 931, 745, SDL_WINDOW_SHOWN)) == nullptr)
		throw "Can't create window";
	if ((mainrend = SDL_CreateRenderer(mainwind, -1, NULL)) == nullptr)
		throw "Can't create renderer";
}

// выделение памяти и загрузка изображений главного экрана игры
void App::MemoryAllocation()
{
	if ((background = new Sprite()) == nullptr)
		throw "Can't allocate memory for background sprite";
	background->loadTexture("images\\Background.png", mainrend);
	background->setPosition(0, 0);
	background->setDimension(931, 745);

	if ((exitbutton = new Sprite()) == nullptr)
		throw "Can't allocate memory for exitbutton sprite";
	exitbutton->loadTexture("images\\ExitButton.png\0", mainrend);
	exitbutton->setPosition(713, 610);
	exitbutton->setDimension(156, 63);

	if ((battleship = new Ship(BATTLESHIP, mainrend)) == nullptr)
		throw "Can't allocate memory for exitbutton sprite";
	battleship->getSprite().loadTexture("images\\Battleship0.png", mainrend);
	battleship->getSprite().setPosition(63, 466);
	battleship->getSprite().setDimension(123, 30);

	if ((cruiser = new Ship(CRUISER, mainrend)) == nullptr)
		throw "Can't allocate memory for exitbutton sprite";
	cruiser->getSprite().loadTexture("images\\Cruiser0.png", mainrend);
	cruiser->getSprite().setPosition(63, 538);
	cruiser->getSprite().setDimension(92, 30);

	if ((submarine = new Ship(SUBMARINE, mainrend)) == nullptr)
		throw "Can't allocate memory for exitbutton sprite";
	submarine->getSprite().loadTexture("images\\Submarine0.png", mainrend);
	submarine->getSprite().setPosition(63, 600);
	submarine->getSprite().setDimension(61, 30);

	if ((boat = new Ship(BOAT, mainrend)) == nullptr)
		throw "Can't allocate memory for exitbutton sprite";
	boat->getSprite().loadTexture("images\\Boat0.png", mainrend);
	boat->getSprite().setPosition(63, 662);
	boat->getSprite().setDimension(30, 30);

	if ((playerfield = new Field(mainrend)) == nullptr)
		throw "Can't allocate memory for player's field";
	playerfield->getMesh().loadTexture("images\\PlayerField.png", mainrend);
	playerfield->getMesh().setPosition(93, 93);
	playerfield->getMesh().setDimension(311, 311);
	playerfield->getAxis().loadTexture("images\\PlayerAxis.png", mainrend);
	playerfield->getAxis().setPosition(62, 62);
	playerfield->getAxis().setDimension(342, 342);


	if ((enemyfield = new Field(mainrend)) == nullptr)
		throw "Can't allocate memory for enemy's field";
	enemyfield->getMesh().loadTexture("images\\EnemyField.png", mainrend);
	enemyfield->getMesh().setPosition(558, 93);
	enemyfield->getMesh().setDimension(311, 311);
	enemyfield->getAxis().loadTexture("images\\EnemyAxis.png", mainrend);
	enemyfield->getAxis().setPosition(527, 62);
	enemyfield->getAxis().setDimension(342, 342);
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
	SDL_SetRenderDrawColor(mainrend, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(mainrend);

	SDL_RenderCopy(mainrend, background->getTexture(), NULL, background->getRect());
	SDL_RenderCopy(mainrend, exitbutton->getTexture(), NULL, exitbutton->getRect());
	if (battleshipnum < 1)
		SDL_RenderCopy(mainrend, battleship->getSprite().getTexture(), NULL, battleship->getSprite().getRect());
	if (cruisernum < 2)
		SDL_RenderCopy(mainrend, cruiser->getSprite().getTexture(), NULL, cruiser->getSprite().getRect());
	if (submarinenum < 3)
		SDL_RenderCopy(mainrend, submarine->getSprite().getTexture(), NULL, submarine->getSprite().getRect());
	if (boatnum < 4)
		SDL_RenderCopy(mainrend, boat->getSprite().getTexture(), NULL, boat->getSprite().getRect());
	
	playerfield->Rendering();
	enemyfield->Rendering();

	if (drag)
		SDL_RenderCopy(mainrend, dragableship->getSprite().getTexture(), NULL, dragableship->getSprite().getRect());

	SDL_RenderPresent(mainrend);
}

int App::Execution()
{
	try
	{
		Initialization();
		MemoryAllocation();
		//connection.Init("192.168.0.106");
		//connection.Connect();
	}
	catch (const char *errormessage)
	{
		cout << errormessage << endl;
		system("pause");
		// Error message
		return 1;
	}

	// TODO:
	// растановка кораблей
	// отпрака сообщения на сервер о том, что корабли расставлены


	drag = false;
	running = true;
	while (running)
	{
		SDL_Event playerevent;
		while (SDL_PollEvent(&playerevent))
		{
			switch (playerevent.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONUP:
				if  (playerevent.button.button == SDL_BUTTON_LEFT)
				{
					if (exitbutton->checkCursorHit(playerevent.button.x, playerevent.button.y))
						running = false;
					// конец перетаскивания корабля
					else if (drag)
					{
						SDL_Rect *ship = dragableship->getSprite().getRect();

						if (playerfield->getMesh().checkCursorHit(ship->x, ship->y) && playerfield->getMesh().checkCursorHit(ship->x + ship->w, ship->y + ship->h) &&
							playerfield->checkPlace(*dragableship))
						{
							playerfield->addShip(*dragableship);
							delete dragableship;
							dragableship = nullptr;
							drag = false;
						}
						else
						{
							if (dragableship->getType() == BATTLESHIP)
								battleshipnum--;
							else if (dragableship->getType() == CRUISER)
								cruisernum--;
							else if (dragableship->getType() == SUBMARINE)
								submarinenum--;
							else if (dragableship->getType() == BOAT)
								boatnum--;
							
							delete dragableship;
							dragableship = nullptr;
							drag = false;
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (playerevent.button.button == SDL_BUTTON_LEFT)
				{
					// Начало перетаскивания корабля
					if (playerfield->getShipCount() < SIZE)
					{
						if (battleship->getSprite().checkCursorHit(playerevent.button.x, playerevent.button.y) && battleshipnum < 1)
						{
							battleshipnum++;
							drag = true;

							dragableship = new Ship();
							*dragableship = *battleship;
						}
						else if (cruiser->getSprite().checkCursorHit(playerevent.button.x, playerevent.button.y) && cruisernum < 2)
						{
							cruisernum++;
							drag = true;

							dragableship = new Ship();
							*dragableship = *cruiser;
						}
						else if (submarine->getSprite().checkCursorHit(playerevent.button.x, playerevent.button.y) && submarinenum < 3)
						{
							submarinenum++;
							drag = true;

							dragableship = new Ship();
							*dragableship = *submarine;
						}
						else if (boat->getSprite().checkCursorHit(playerevent.button.x, playerevent.button.y) && boatnum < 4)
						{
							boatnum++;
							drag = true;

							dragableship = new Ship();
							*dragableship = *boat;
						}
					}

					if (playerfield->getMesh().checkCursorHit(playerevent.button.x, playerevent.button.y))
					{
						cout << playerevent.button.x << " " << playerevent.button.y << endl;
					}
				}
				// поворот корабля при перетаскивании
				else if (playerevent.button.button == SDL_BUTTON_RIGHT)
				{
					if (drag)
					{
						SDL_Rect *ship = dragableship->getSprite().getRect();
						dragableship->rotation();
						dragableship->getSprite().setPosition(playerevent.button.x - 15, playerevent.button.y - 15);
					}
				}
				break;
			case SDL_MOUSEMOTION:
				// обработка перетаскивания корабля
				if (drag)
				{
					SDL_Rect *ship = dragableship->getSprite().getRect();
					SDL_Point mouse = {playerevent.motion.x , playerevent.motion.y };

					if (playerfield->getMesh().checkCursorHit(mouse.x, mouse.y) &&
						playerfield->getMesh().checkCursorHit(ship->x, ship->y) && 
						playerfield->getMesh().checkCursorHit(ship->x + ship->w, ship->y + ship->h))
					{
						int fx = 0, fy = 0;
						playerfield->CoordWindToField(&mouse.x, &mouse.y, &fx, &fy);
						playerfield->CoordFieldToWind(&mouse.x, &mouse.y, &fx, &fy);
						dragableship->getSprite().setPosition(mouse.x, mouse.y);
					}
					else
					{
						dragableship->getSprite().setPosition(mouse.x - 15, mouse.y - 15);
					}
				}
				break;
			}
		}

		

		Rendering();
	}


	return 0;
}