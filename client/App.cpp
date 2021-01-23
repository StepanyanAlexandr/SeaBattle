#include "App.h"

App::App()
{
	mainwind = nullptr;
	mainrend = nullptr;

	background = nullptr;
	exitbutton = nullptr;
	playbutton = nullptr;

	battleship = nullptr;
	cruiser = nullptr;
	submarine = nullptr;
	boat = nullptr;
	dragableship = nullptr;

	playerfield = nullptr;
	enemyfield = nullptr;

	running = true;

	stage = PLACINGSHIPS;
}

App::~App()
{
	if (background != nullptr) delete background;
	if (exitbutton != nullptr) delete exitbutton;
	if (playbutton != nullptr) delete playbutton;
	if (playerfield != nullptr) delete playerfield;
	if (enemyfield != nullptr) delete enemyfield;
	if (battleship != nullptr) delete battleship;
	if (cruiser != nullptr) delete cruiser;
	if (submarine != nullptr) delete submarine;
	if (boat != nullptr) delete boat;
	if (dragableship != nullptr) delete dragableship;

	Close();
}

// Удаление окна и рендера, закрытие соединения
void App::Close()
{
	SDL_DestroyRenderer(mainrend);
	SDL_DestroyWindow(mainwind);
	SDL_Quit();
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
	if (stage == PLACINGSHIPS)
	{
		boatnum = 0;
		submarinenum = 0;
		cruisernum = 0;
		battleshipnum = 0;

		drag = false;
		turn = false;
		iswin = false;

		if (background != nullptr) delete background;
		if (exitbutton != nullptr) delete exitbutton;

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

		if ((playbutton = new Sprite()) == nullptr)
			throw "Can't allocate memory for playbutton sprite";
		playbutton->loadTexture("images\\PlayButton.png\0", mainrend);
		playbutton->setPosition(713, 527);
		playbutton->setDimension(156, 63);

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
		playerfield->LoadTockens();

		if ((enemyfield = new Field(mainrend)) == nullptr)
			throw "Can't allocate memory for enemy's field";
		enemyfield->getMesh().loadTexture("images\\EnemyField.png", mainrend);
		enemyfield->getMesh().setPosition(558, 93);
		enemyfield->getMesh().setDimension(311, 311);
		enemyfield->getAxis().loadTexture("images\\EnemyAxis.png", mainrend);
		enemyfield->getAxis().setPosition(527, 62);
		enemyfield->getAxis().setDimension(342, 342);
		enemyfield->LoadTockens();

		SDL_SetWindowSize(mainwind, 931, 745);
		SDL_SetWindowPosition(mainwind, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	else if (stage == GAME)
	{
		if (playbutton != nullptr) { delete playbutton; playbutton = nullptr; }
		if (battleship != nullptr) { delete battleship; battleship = nullptr; }
		if (cruiser != nullptr) { delete cruiser; cruiser = nullptr; }
		if (submarine != nullptr) { delete submarine; submarine = nullptr; }
		if (boat != nullptr) { delete boat; boat = nullptr; }
		if (dragableship != nullptr) { delete dragableship; dragableship = nullptr; }
	}
	else if (stage == ENDGAME)
	{
		if (background != nullptr) delete background;
		if (playerfield != nullptr) delete playerfield;
		if (enemyfield != nullptr) delete enemyfield;
		if (exitbutton != nullptr) delete exitbutton;
		
		if ((background = new Sprite()) == nullptr)
			throw "Can't allocate memory for background sprite";
		if (iswin) background->loadTexture("images\\VictoryBackground.png", mainrend);
		else background->loadTexture("images\\DefeatBackground.png", mainrend);
		background->setPosition(0, 0);
		background->setDimension(800, 400);
		
		if ((exitbutton = new Sprite()) == nullptr)
			throw "Can't allocate memory for exitbutton sprite";
		exitbutton->loadTexture("images\\ExitButton.png\0", mainrend);
		exitbutton->setPosition(600, 300);
		exitbutton->setDimension(156, 63);

		SDL_SetWindowSize(mainwind, 800, 400);
		SDL_SetWindowPosition(mainwind, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
}

void App::Rendering()
{
	SDL_SetRenderDrawColor(mainrend, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(mainrend);

	if (stage == PLACINGSHIPS)
	{
		SDL_RenderCopy(mainrend, background->getTexture(), NULL, background->getRect());
		SDL_RenderCopy(mainrend, exitbutton->getTexture(), NULL, exitbutton->getRect());
		SDL_RenderCopy(mainrend, playbutton->getTexture(), NULL, playbutton->getRect());
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
	}
	else if (stage == GAME)
	{
		SDL_RenderCopy(mainrend, background->getTexture(), NULL, background->getRect());
		SDL_RenderCopy(mainrend, exitbutton->getTexture(), NULL, exitbutton->getRect());

		playerfield->Rendering();
		enemyfield->Rendering();
	}
	else if (stage == ENDGAME)
	{
		SDL_RenderCopy(mainrend, background->getTexture(), NULL, background->getRect());
		SDL_RenderCopy(mainrend, exitbutton->getTexture(), NULL, exitbutton->getRect());
	}
	
	SDL_RenderPresent(mainrend);
}

int App::Execution()
{
	// инициализируем SDL и SDL_image,
	// создаем окно и получаем связанный с ним рендерер
	try { Initialization(); }
	catch (const char *errormessage)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errormessage, NULL);
		running = false;
	}

	// основной цикл программы 
	while (running)
	{
		// выделяем необходимую память
		try { MemoryAllocation(); }
		catch (const char *errormessage)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errormessage, NULL);
			running = false;
		}

		bool isStageEnd = false;
		// основной цикл первого этапа работы программы - расстановка кораблей
		while (running && stage == PLACINGSHIPS)
		{
			// Цикл обработки пользовательских событий
			SDL_Event playerevent;
			while (SDL_PollEvent(&playerevent))
			{
				// На этом этапе игры будем обрабатывать несколько типов событий:
				//	1.	Закрытие приложения нажатием на крестик.
				//	2.	Отпускание левой кнопки мыши. В этом случае обрабатываем нажатие кнопки выхода из игры, 
				// нажатие кнопки начала игры, при выставленных на поле кораблях или отпускание перетаскиваемого корабля (конечный этап события drag'n'drop).
				//  3.	Нажатие кнопки мыши. Если нажата правая кнопка мыши и при этом курсор находится над кораблем,
				// то начинаем перетаскивать этот корабль (начало события drag'n'drop). Если же нажата правая кнопка мыши и при этом перетаскивается корабль,
				// то его нужно повернуть.
				// 4.	Движения мыши, в момент перетаскивания корабля, что бы корректно отрисовать перетаскиваемый корабль.

				switch (playerevent.type)
				{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEBUTTONUP:
					if (playerevent.button.button == SDL_BUTTON_LEFT)
					{
						// если была нажата кнопка выхода
						if (exitbutton->checkCursorHit(playerevent.button.x, playerevent.button.y))
							running = false;
						// если корабли расставлены и нажата кнопка играть
						else if (playbutton->checkCursorHit(playerevent.button.x, playerevent.button.y) && playerfield->getShipCount() == SIZE)
							isStageEnd = true;
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
						SDL_Point mouse = { playerevent.motion.x , playerevent.motion.y };

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
			// Отрисовывка графики на экран
			Rendering();

			if (isStageEnd)
				stage = GAME;
		}

		if (running)
		{
			// Если приложение не было закрыто на предыдущем этапе
			// Освобождаем ненужную память и пытаемся подключится к серверу
			try
			{
				MemoryAllocation();
				connection.Init();
				// устанавливаем соединение с сервером
				for (int i = 0; i < 5 && !connection.isConnect(); i++)
				{
					connection.Connect();
					SDL_Delay(300);
				}
				if (!connection.isConnect())
					throw "Couldn't connected to server";
			}
			catch (const char *errormessage)
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errormessage, NULL);
				running = false;
			}

			// Отправляем на сервер сообщение с информацией о расстановке кораблей на поле
			string message = playerfield->getShipsPlacement();
			connection.MessageSend(message);

			// принимаем ответ от сервера
			// в нем содержится информация о том, чей сейчас ход
			connection.MessageReceve();
			message = connection.getLastInputMessage();
			if (message == "yourturn:") turn = true;
			else if (message == "enemyturn") turn = false;

			SDL_Point hit = { -1, -1 };
			isStageEnd = false;
			// основной цикл второго этапа работы программы - игра по сети
			while (running && stage == GAME)
			{
				hit = { -1, -1 };
				message = "";

				// Цикл обработки пользовательских событий
				SDL_Event playerevent;
				while (SDL_PollEvent(&playerevent))
				{
					// Здесь обрабатываются следующие типы событий:
					//	1.	Закрытие приложения нажатием на крестик.
					//	2.	Отпускание левой кнопки мыши. В этом случае обрабатываем нажатие кнопки выхода из игры или выстрел по противнику

					switch (playerevent.type)
					{
					case SDL_QUIT:
						running = false;
						break;
					case SDL_MOUSEBUTTONUP:
						if (playerevent.button.button == SDL_BUTTON_LEFT)
						{
							if (exitbutton->checkCursorHit(playerevent.button.x, playerevent.button.y))
								running = false;
							else if (turn && enemyfield->getMesh().checkCursorHit(playerevent.button.x, playerevent.button.y))
							{
								int x = 0, y = 0;
								enemyfield->CoordWindToField(&playerevent.button.x, &playerevent.button.y, &x, &y);
								if (enemyfield->checkCell(x, y))
									hit = { x, y };
							}
						}
						break;
					}
				}

				// клиент должен отправить одно сообщение на сервер при каждом повторении цикла
				//		если этот клиент завершает работу, то посылается сообщение disconnect: 
				//		при этом ответ от сервера не ожидается
				//
				//		если этот клиент сделал выстрел на своем ходу, то посылается сообщение hit:pos_x:pos_y:
				//		в этом случае от сервера ожидается цепочка из двух сообщений
				//
				//		если клиент не сделал никаких действий, либо сейчас не его ход, то сервер пингуется (ping:)
				//		количество ответных сообщений зависит от информации из первого сообщения от сервера

				if (!running)
				{
					// сообщаем серверу о том, что отключаемся
					message = "disconnect:";
					connection.MessageSend(message);
				}
				else if (turn && hit.x != -1 && hit.y != -1)
				{
					// отправляем серверу сообщении о выстреле и координаты ячейки куда выстрелили
					message = "hit:";
					message += (hit.x + '0');
					message += ':';
					message += (hit.y + '0');
					message += ':';
					connection.MessageSend(message);

					// получаем от сервера сообщение с информацией о попадании/промахе/уничтожении корабля
					connection.MessageReceve();
					message = connection.getLastInputMessage();
					if (message[6] == 'M') enemyfield->setMiss(hit.x, hit.y);
					else if (message[6] == 'H') enemyfield->setHit(hit.x, hit.y);
					else if (message[6] == 'D') enemyfield->destroyShip(hit.x, hit.y);

					// принимаем второе сообщение от сервера о победе или просто пинг
					connection.MessageReceve();
					message = connection.getLastInputMessage();
					if (message == "win:")
					{
						iswin = true;
						isStageEnd = true;
					}
					else
						turn = false;
				}
				else
				{
					// пингуем сервер
					message = "ping:";
					connection.MessageSend(message);

					// получаем ответ от сервера
					connection.MessageReceve();
					message = connection.getLastInputMessage();

					if (turn)
					{
						// на пинг сервера во время хода этого клиента могут поступить следующие ответы
						// сообщение может говорить о победе этого клиента
						// либо там будет ответный пинг от сервера
						if (message == "win:")
						{
							iswin = true;
							isStageEnd = true;
						}
					}
					else
					{
						// на пинг сервера во время хода противника могут поступить следующие ответы
						// player:hit_info:pos_x:pos_y - противник сделал выстрел, в данном сообщении содержится информация о нем
						// win: - противник вышел, этот клиент побеждает
						// либо просто ответный пинг от сервера, если противник еще не сходил

						if (message.find("player:") != string::npos)
						{
							int x = (message[9] - '0'), y = (message[11] - '0');
							if (message[7] == 'M') playerfield->setMiss(x, y);
							else if (message[7] == 'H') playerfield->setHit(x, y);
							else if (message[7] == 'D') playerfield->destroyShip(x, y);

							// если противник сделал выстрел и от сервера пришло сообщение об этом
							// то сервер отправляет следом еще одно сообщение
							// оно может содержать либо информацию о проигрыше этого клиента
							// либо пинг клиента
							connection.MessageReceve();
							message = connection.getLastInputMessage();
							if (message == "lose:")
							{
								iswin = false;
								isStageEnd = true;
							}
							else
								turn = true;
						}
						else if (message == "win:")
						{
							iswin = true;
							isStageEnd = true;
						}
					}
				}
				// Отрисовывка графики на экран
				Rendering();
				
				if (isStageEnd)
					stage = ENDGAME;
			}

			connection.Close();
		}

		if (running)
		{
			// перераспределяем память необходимую для этапа ENDGAME
			try { MemoryAllocation(); }
			catch (const char *errormessage)
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errormessage, NULL);
				running = false;
			}

			isStageEnd = false;
			while (running && stage == ENDGAME)
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
						if (playerevent.button.button == SDL_BUTTON_LEFT)
							if (exitbutton->checkCursorHit(playerevent.button.x, playerevent.button.y))
								isStageEnd = true;
						break;
					}
				}

				Rendering();
				
				if (isStageEnd)
					stage = PLACINGSHIPS;
			}
		}
	}



	return 0;
}