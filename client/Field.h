#pragma once
#include "Sprite.h"
#include "Ship.h"
#include <iostream>
using namespace std;

#define SIZE (10)

typedef enum CELLTYPE
{
	EMPTY = 0,
	SHIP,
	MISS,
	HIT,
	DESTROY
}CELLTYPE;

class Field
{
private:
	SDL_Renderer *render;

	Sprite* mesh;
	CELLTYPE **field;
	Ship** ships;

	int shipcount;

public:
	Field(SDL_Renderer *rend, const char* path);
	~Field();

	//void setCell(celltype type, int x, int y) { field[x][y] = type; }
	Sprite& getSprite() { return *mesh; }
	bool checkPlace(const int x, const int y) const;
	void addShip(const SHIPTYPE type) { if (shipcount != SIZE) ships[shipcount++] = new Ship(type, render); }
	Ship& getShip(const int pos) { return *ships[pos]; }
	int getShipCount() const { return shipcount; }

	CELLTYPE& operator() (const int x, const int y) { return field[x][y]; }
};

Field::Field(SDL_Renderer *rend, const char* path) : render(rend), mesh(nullptr), field(nullptr), shipcount(0)
{
	mesh = new Sprite;
	mesh->loadTexture(path, render);
	mesh->setPosition(40, 40);
	mesh->setDimension(342, 342);

	field = new CELLTYPE*[10];
	ships = new Ship*[10];
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
		delete[] field[i];
	delete[] field;
}

bool Field::checkPlace(const int x, const int y) const
{
	if (field[x][y] == SHIP		|| field[x][y + 1] == SHIP	   || field[x][y - 1] == SHIP ||
		field[x + 1][y] == SHIP || field[x + 1][y + 1] == SHIP || field[x + 1][y - 1] == SHIP ||
		field[x - 1][y] == SHIP || field[x - 1][y + 1] == SHIP || field[x - 1][y - 1] == SHIP)
	{
		return false;
	}
	return true;
}