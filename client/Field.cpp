#include "Field.h"

Field::Field(SDL_Renderer *rend) : render(rend), mesh(nullptr), axis(nullptr), field(nullptr), shipcount(0)
{
	mesh = new Sprite();
	axis = new Sprite();

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
		delete ships[i];
		delete[] field[i];
	}
	delete[] ships;
	delete[] field;
	delete mesh;
	delete axis;
}

Sprite& Field::getTocken(const CELLTYPE celltype)
{
	if (celltype == MISS) return tockens[MISS];
	else if (celltype == HIT) return tockens[HIT];
	else if (celltype == DESTROY) return tockens[DESTROY];
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

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			SDL_Rect rect;
			if (field[i][j] != SHIP && field[i][j] != EMPTY)
			{
				rect.w = 30;
				rect.h = 30;
				CoordFieldToWind(&rect.x, &rect.y, &i, &j);
				SDL_RenderCopy(render, tockens[field[i][j]].getTexture(), NULL, &rect);
			}
		}
	}
}