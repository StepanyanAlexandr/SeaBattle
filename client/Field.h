#pragma once
#include "Ship.h"

#define SIZE (10)

typedef enum CELLTYPE
{
	EMPTY = 0,
	SHIP,
	MISS,
	HIT
}CELLTYPE;

class Field
{
private:
	SDL_Renderer *render;

	Sprite *mesh;		// mesh - хранит спрайт сетки поля
	Sprite *axis;		// axis - хранит спрайт координат клеток
	Sprite *miss;
	Sprite *hit;
	CELLTYPE **field;	
	
	Ship **ships;
	int shipcount;

public:
	Field(SDL_Renderer *rend);
	~Field();

	void LoadTockens();

	void setMiss(const int x, const int y);
	void setHit(const int x, const int y);
	void destroyShip(const int x, const int y);
	
	Sprite& getMesh() { return *mesh; }
	Sprite& getAxis() { return *axis; }
	CELLTYPE getCell(const int i, const int j) { return field[i][j]; }
	Ship& getShip(const int pos) { return *ships[pos]; }
	int getShipCount() const { return shipcount; }

	bool checkPlace(Ship& ship) const;
	bool checkCell(const int x, const int y) const;

	void addShip(Ship& ship);

	void CoordWindToField(int *windx, int *windy, int *fieldx, int *fieldy) const;
	void CoordFieldToWind(int *windx, int *windy, int *fieldx, int *fieldy) const;

	void Rendering();

	string getShipsPlacement();
};