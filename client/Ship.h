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
const char shipassets[16][23] =
{
	"images\\Boat0.png",
	"images\\Boat1.png",
	"images\\Boat2.png",
	"images\\Boat3.png",

	"images\\Submarine0.png",
	"images\\Submarine1.png",
	"images\\Submarine2.png",
	"images\\Submarine3.png",

	"images\\Cruiser0.png",
	"images\\Cruiser1.png",
	"images\\Cruiser2.png",
	"images\\Cruiser3.png",

	"images\\Battleship0.png",
	"images\\Battleship1.png",
	"images\\Battleship2.png",
	"images\\Battleship3.png"
};

extern int dimension[8][2];

class Ship
{
private:
	SDL_Renderer *render;
	
	Sprite *sprite;
	SHIPTYPE type;
	int direction;
public:
	Ship() : render(nullptr), sprite(nullptr) {}
	Ship(const SHIPTYPE t, SDL_Renderer *rend);
	Ship(const Ship& right) { *this = right; }
	~Ship() { delete sprite; }

	Sprite& getSprite() { return *sprite; }
	SHIPTYPE getType() const { return type; }
	int getDirection() const { return direction; }

	void rotation();

	Ship& operator= (const Ship& right);
};