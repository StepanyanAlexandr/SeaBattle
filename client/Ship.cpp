#include "Ship.h"

int dimension[8][2] =
{
	{30, 30},	{30, 30},
	{61, 30},	{30, 61},
	{92, 30},	{30, 92},
	{123, 30},	{30, 123}
};


Ship::Ship(SHIPTYPE t, SDL_Renderer *rend) : sprite(nullptr), render(rend), direction(0), type(t)
{
	sprite = new Sprite();

	sprite->loadTexture(shipassets[type * 4 + direction], render);
	sprite->setDimension(dimension[type * 2 + direction % 2][0], dimension[type * 2 + direction % 2][1]);
}

// поворот корабля
void Ship::rotation()
{
	if (direction != 3)
		direction++;
	else
		direction = 0;

	sprite->setDimension(dimension[type * 2 + direction % 2][0], dimension[type * 2 + direction % 2][1]);
	sprite->loadTexture(shipassets[type * 4 + direction], render);
}

Ship& Ship::operator= (const Ship& right)
{
	render = nullptr;
	if (sprite != nullptr)
		delete sprite;
	sprite = nullptr;

	render = right.render;
	type = right.type;
	direction = right.direction;

	sprite = new Sprite();
	sprite->loadTexture(shipassets[type * 4 + direction], render);
	sprite->setPosition(right.sprite->getRect()->x, right.sprite->getRect()->y);
	sprite->setDimension(right.sprite->getRect()->w, right.sprite->getRect()->h);

	return *this;
}