#pragma once
#include "Ship.h"

#define SIZE (10)

typedef enum CELLTYPE
{
	DESTROY = 0,
	MISS,
	HIT,
	SHIP,
	EMPTY,
}CELLTYPE;

class Field
{
private:
	SDL_Renderer *render;

	Sprite *mesh;		// mesh - хранит спрайт сетки поля
	Sprite *axis;		// axis - хранит спрайт координат клеток
	Sprite tockens[3];	// здесь хранятся спрайты для клетки поля
	CELLTYPE **field;	
	
	Ship **ships;
	int shipcount;

public:
	Field(SDL_Renderer *rend);
	~Field();

	void setCell(CELLTYPE type, int x, int y) { field[x][y] = type; }
	
	Sprite& getMesh() { return *mesh; }
	Sprite& getAxis() { return *axis; }
	Sprite& getTocken(const CELLTYPE celltype);
	CELLTYPE getCell(const int i, const int j) { return field[i][j]; }
	Ship& getShip(const int pos) { return *ships[pos]; }
	int getShipCount() const { return shipcount; }

	bool checkPlace(const int x, const int y) const;
	void addShip(const Ship& ship) { ships[shipcount] = new Ship(ship);	shipcount++; }

	void CoordWindToField(int *windx, int *windy, int *fieldx, int *fieldy);
	void CoordFieldToWind(int *windx, int *windy, int *fieldx, int *fieldy);

	void Rendering();
};