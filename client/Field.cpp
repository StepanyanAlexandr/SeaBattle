#include "Field.h"

Field::Field(SDL_Renderer *rend) : render(rend), mesh(nullptr), axis(nullptr), field(nullptr), shipcount(0)
{
	mesh = new Sprite();
	axis = new Sprite();
	miss = new Sprite();
	hit = new Sprite();

	field = new CELLTYPE*[SIZE];
	ships = new Ship*[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		field[i] = new CELLTYPE[10];
		ships[i] = nullptr;
		for (int j = 0; j < SIZE; j++)
			field[i][j] = EMPTY;
	}
}

Field::~Field()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (ships[i] != nullptr) delete ships[i];
		delete[] field[i];
	}
	delete[] ships;
	delete[] field;
	delete mesh;
	delete axis;
	delete miss;
	delete hit;
}

void Field::LoadTockens()
{
	miss->loadTexture("images\\Miss.png", render);
	miss->setDimension(30, 30);

	hit->loadTexture("images\\Hit.png", render);
	hit->setDimension(30, 30);
}

void Field::setHit(const int x, const int y) 
{ 
	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) 
		field[x][y] = HIT; 
}

void Field::setMiss(const int x, const int y) 
{ 
	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && field[x][y] == EMPTY) 
		field[x][y] = MISS; 
}

void Field::destroyShip(const int x, const int y)
{
	field[x][y] = HIT;

	if ((x == 0 || field[x - 1][y] == MISS || field[x - 1][y] == EMPTY) &&
		(x == SIZE - 1 || field[x + 1][y] == MISS || field[x + 1][y] == EMPTY) &&
		(y == 0 || field[x][y - 1] == MISS || field[x][y - 1] == EMPTY) &&
		(y == SIZE - 1 || field[x][y + 1] == MISS || field[x][y + 1] == EMPTY))
	{
		setMiss(x - 1, y);
		setMiss(x + 1, y);
		setMiss(x, y - 1);
		setMiss(x, y + 1);
		setMiss(x - 1, y - 1);
		setMiss(x - 1, y + 1);
		setMiss(x + 1, y - 1);
		setMiss(x + 1, y + 1);
	}
	else
	{
		int curx = x, cury = y, prevx = x, prevy = y;
		while (true)
		{
			bool flag = true;

			if (curx != 0 && curx - 1 != prevx && field[curx - 1][cury] == HIT)
			{
				prevx = curx;
				curx--;
				flag = false;
			}
			else if (curx != SIZE - 1 && curx + 1 != prevx && field[curx + 1][cury] == HIT)
			{
				prevx = curx;
				curx++;
				flag = false;
			}
			else if (cury != 0 && cury - 1 != prevy && field[curx][cury - 1] == HIT)
			{
				prevy = cury;
				cury--;
				flag = false;
			}
			else if (cury != SIZE - 1 && cury + 1 != prevy && field[curx][cury + 1] == HIT)
			{
				prevy = cury;
				cury++;
				flag = false;
			}
			if (flag)
				break;
		}

		int step = 0;
		if (curx != prevx)
		{
			step = prevx - curx;
			for (int i = curx; i >= 0 && i < SIZE && field[i][cury] != MISS && field[i][cury] != EMPTY; i += step)
			{
				setMiss(i - 1, cury);
				setMiss(i + 1, cury);
				setMiss(i, cury - 1);
				setMiss(i, cury + 1);
				setMiss(i - 1, cury - 1);
				setMiss(i - 1, cury + 1);
				setMiss(i + 1, cury - 1);
				setMiss(i + 1, cury + 1);
			}	
		}
		else if (cury != prevy)
		{
			step = prevy - cury;
			for (int i = cury; i >= 0 && i < SIZE && field[curx][i] != MISS && field[curx][i] != EMPTY; i += step)
			{
				setMiss(curx - 1, i);
				setMiss(curx + 1, i);
				setMiss(curx, i - 1);
				setMiss(curx, i + 1);
				setMiss(curx - 1, i - 1);
				setMiss(curx - 1, i + 1);
				setMiss(curx + 1, i - 1);
				setMiss(curx + 1, i + 1);
			}		
		}
	}
}

bool Field::checkPlace(Ship& ship) const
{
	int x = 0, y = 0;
	SDL_Rect *rect = ship.getSprite().getRect();

	if (ship.getDirection() == 0 || ship.getDirection() == 2)
	{
		int j = rect->y + 15;
		for (int i = rect->x + 15; i < rect->x + rect->w; i += 31)
		{
			CoordWindToField(&i, &j, &x, &y);
			if (field[x][y] == SHIP) { return false; }
			if (y != 9 && field[x][y + 1] == SHIP) { return false; }
			if (y != 0 && field[x][y - 1] == SHIP) { return false; }
			if (x != 9 && field[x + 1][y] == SHIP) { return false; }
			if (x != 0 && field[x - 1][y] == SHIP) { return false; }
			if (x != 9 && y != 9 && field[x + 1][y + 1] == SHIP) { return false; }
			if (x != 9 && y != 0 && field[x + 1][y - 1] == SHIP) { return false; }
			if (x != 0 && y != 9 && field[x - 1][y + 1] == SHIP) { return false; }
			if (x != 0 && y != 0 && field[x - 1][y - 1] == SHIP) { return false; }
		}
	}
	else
	{
		int j = rect->x + 15;
		for (int i = rect->y + 15; i < rect->y + rect->h; i += 31)
		{
			CoordWindToField(&j, &i, &x, &y);
			if (field[x][y] == SHIP) { return false; }
			if (y != 9 && field[x][y + 1] == SHIP) { return false; }
			if (y != 0 && field[x][y - 1] == SHIP) { return false; }
			if (x != 9 && field[x + 1][y] == SHIP) { return false; }
			if (x != 0 && field[x - 1][y] == SHIP) { return false; }
			if (x != 9 && y != 9 && field[x + 1][y + 1] == SHIP) { return false; }
			if (x != 9 && y != 0 && field[x + 1][y - 1] == SHIP) { return false; }
			if (x != 0 && y != 9 && field[x - 1][y + 1] == SHIP) { return false; }
			if (x != 0 && y != 0 && field[x - 1][y - 1] == SHIP) { return false; }
		}
	}
	return true;
}

bool Field::checkCell(const int x, const int y) const
{
	if (field[x][y] == SHIP || field[x][y] == EMPTY)
		return true;
	return false;
}

void Field::addShip(Ship& ship)
{ 
	int x = 0, y = 0;
	SDL_Rect *rect = ship.getSprite().getRect();

	if (ship.getDirection() == 0 || ship.getDirection() == 2)
	{
		int j = rect->y + 15;
		for (int i = rect->x + 15; i < rect->x + rect->w; i += 31)
		{
			CoordWindToField(&i, &j, &x, &y);
			field[x][y] = SHIP;
		}
	}
	else
	{
		int j = rect->x + 15;
		for (int i = rect->y + 15; i < rect->y + rect->h; i += 31)
		{
			CoordWindToField(&j, &i, &x, &y);
			field[x][y] = SHIP;
		}
	}
	ships[shipcount] = new Ship(ship);	
	shipcount++; 
}

void Field::CoordWindToField(int *windx, int *windy, int *fieldx, int *fieldy) const
{
	SDL_Rect *start = mesh->getRect();
	*fieldx = (*windx - start->x - 1) / 31;
	*fieldy = (*windy - start->y - 1) / 31;

	if (*fieldx > 9)
		*fieldx = 9;
	if (*fieldy > 9)
		*fieldy = 9;
}

void Field::CoordFieldToWind(int *windx, int *windy, int *fieldx, int *fieldy) const
{
	SDL_Rect *start = mesh->getRect();
	*windx = *fieldx * 31 + start->x + 1;
	*windy = *fieldy * 31 + start->y + 1;
}

void Field::Rendering()
{
	SDL_RenderCopy(render, axis->getTexture(), NULL, axis->getRect());
	SDL_RenderCopy(render, mesh->getTexture(), NULL, mesh->getRect());

	for (int i = 0; i < shipcount; i++)
		SDL_RenderCopy(render, ships[i]->getSprite().getTexture(), NULL, ships[i]->getSprite().getRect());

	int x, y;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (field[i][j] == MISS)
			{
				CoordFieldToWind(&x, &y, &i, &j);
				miss->setPosition(x, y);
				SDL_RenderCopy(render, miss->getTexture(), NULL, miss->getRect());
			}
			else if (field[i][j] == HIT)
			{
				CoordFieldToWind(&x, &y, &i, &j);
				hit->setPosition(x, y);
				SDL_RenderCopy(render, hit->getTexture(), NULL, hit->getRect());
			}
		}
	}
}

string Field::getShipsPlacement()
{
	string placement = "";
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (field[i][j] == EMPTY) placement += '0';
			else placement += '1';
	placement += ':';
	return placement;
}