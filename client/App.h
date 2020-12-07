#pragma once
#include "Connection.h"

typedef enum celltype
{
	EMPTY = 0,
	SHIP,
	MISS,
	HIT,
	DESTROY
}celltype;

class App
{
private:
	bool	 running;
	celltype field[10][10];
public:
	App();
	~App();

	void	 setcell(celltype type, int x, int y) { field[x][y] = type; }
	celltype getcell(int x, int y) { return field[x][y]; }
};