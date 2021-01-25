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