#pragma once
#include "Sprite.h"

typedef enum SHIPTYPE
{
	BOAT = 0,		// 1 палуба
	SUBMARINE,		// 2 палубы
	CRUISER,		// 3 палубы
	BATTLESHIP		// 4 палубы
}SHIPTYPE;

// пути к файлам со спрайтами кораблей в разных положениях
const char shipassets[16][24] =
{
	"images\\Boat0.png\0",
	"images\\Boat1.png\0",
	"images\\Boat2.png\0",
	"images\\Boat3.png\0",

	"images\\Submarine0.png\0",
	"images\\Submarine1.png\0",
	"images\\Submarine2.png\0",
	"images\\Submarine3.png\0",

	"images\\Cruiser0.png\0",
	"images\\Cruiser1.png\0",
	"images\\Cruiser2.png\0",
	"images\\Cruiser3.png\0",

	"images\\Battleship0.png\0",
	"images\\Battleship1.png\0",
	"images\\Battleship2.png\0",
	"images\\Battleship3.png\0"
};

int dimension[8][2] = 
{ 
	{32, 32},	{32, 32}, 
	{63, 32},	{32, 63}, 
	{94, 32},	{32, 94}, 
	{125, 32},	{32, 125} 
};

class Ship
{
private:
	SDL_Renderer *render;
	
	Sprite *sprite;
	SHIPTYPE type;
	int direction;
public:
	Ship(const SHIPTYPE t, SDL_Renderer *rend);
	~Ship() { delete sprite; }

	Sprite& getSprite() { return *sprite; }
	SHIPTYPE getType() const { return type; }
	
	void rotation();
};

Ship::Ship(SHIPTYPE t, SDL_Renderer *rend) : sprite(nullptr), render(rend), direction(0), type(t)
{
	sprite = new Sprite();

	sprite->loadTexture(shipassets[type * 4 + direction], render);
	sprite->setDimension(dimension[type + direction % 2][0], dimension[type + direction % 2][1]);
}

// поворот корабля
void Ship::rotation()
{
	if (direction != 3)
		direction++;
	else
		direction == 0;

	sprite->loadTexture(shipassets[type * 4 + direction], render);
	sprite->setDimension(dimension[type + direction % 2][0], dimension[type + direction % 2][1]);
}