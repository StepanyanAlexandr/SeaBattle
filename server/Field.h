#pragma once
#include "Connection.h"

#define SIZE 10

typedef enum CELLTYPE
{
	DESTROY = 0,
	MISS,
	HIT,
	SHIP,
	EMPTY,
}CELLTYPE;

#define FIRSTPLAYER 0
#define SECONDPLAYER 1

class Field
{
private:
	CELLTYPE **field;
public:
	Field(const string &cells);
	~Field();

	void setMiss(const int x, const int y) { if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && field[x][y] == EMPTY) field[x][y] = MISS; }
	void setHit(const int x, const int y) { if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && field[x][y] == SHIP) field[x][y] = HIT; }
	void destroyShip(const int x, const int y);
	
	CELLTYPE hitType(const int x, const int y) const;
	bool isWin();
};

Field::Field(const string &cells)
{
	field = new CELLTYPE*[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		field[i] = new CELLTYPE[SIZE];
		for (int j = 0; j < SIZE; j++)
		{
			if (cells[SIZE * i + j] == '1')
				field[i][j] = SHIP;
			else
				field[i][j] = EMPTY;
		}
	}
}

Field::~Field()
{
	for (int i = 0; i < SIZE; i++)
		delete[] field[i];
	delete[] field;
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
				setHit(curx, i);
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

CELLTYPE Field::hitType(const int x, const int y) const
{
	if (field[x][y] == EMPTY)
		return MISS;

	if (x != 0 && field[x - 1][y] == SHIP || x != (SIZE - 1) && field[x + 1][y] == SHIP ||
		y != 0 && field[x][y - 1] == SHIP || y != (SIZE - 1) &&  field[x][y + 1] == SHIP)
		return HIT;
	if ((x == 0 || field[x - 1][y] == MISS || field[x - 1][y] == EMPTY) &&
		(x == SIZE - 1 || field[x + 1][y] == MISS || field[x + 1][y] == EMPTY) &&
		(y == 0 || field[x][y - 1] == MISS || field[x][y - 1] == EMPTY) &&
		(y == SIZE - 1 || field[x][y + 1] == MISS || field[x][y + 1] == EMPTY))
		return DESTROY;

	int curx = x, cury = y, prevx = x, prevy = y;
	while (true)
	{
		bool flag = true;

		if (curx != 0 && curx - 1 != prevx && ( field[curx - 1][cury] == HIT || field[curx - 1][cury] == SHIP ))
		{
			prevx = curx;
			curx--;
			flag = false;
		}
		else if (curx != SIZE - 1 && curx + 1 != prevx && ( field[curx + 1][cury] == HIT || field[curx + 1][cury] == SHIP ))
		{
			prevx = curx;
			curx++;
			flag = false;
		}
		else if (cury != 0 && cury - 1 != prevy && (field[curx][cury - 1] == HIT || field[curx][cury - 1] == SHIP ))
		{
			prevy = cury;
			cury--;
			flag = false;
		}
		else if (cury != SIZE - 1 && cury + 1 != prevy && ( field[curx][cury + 1] == HIT || field[curx][cury + 1] == SHIP ))
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
			if (i != x && field[i][cury] == SHIP)
				return HIT;
	}
	else if (cury != prevy)
	{
		step = prevy - cury;
		for (int i = cury; i >= 0 && i < SIZE && field[curx][i] != MISS && field[curx][i] != EMPTY; i += step)
			if (i != y && field[curx][i] == SHIP)
				return HIT;
	}

	return DESTROY;
}

bool Field::isWin()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (field[i][j] == SHIP)
				return false;
	return true;
}