#include <iostream>
#include "point.h"
#include "board.h"
#include "shape.h"

board::board()
{
	for (int i = 0; i < 12; i++)
	{
		usedCoords[19][i] = 1;
	}
}

bool board::existInMat(point val)
{
	if (usedCoords[val.getY()][val.getX()] != 0) // changed x/y
		return true;
	else
		return false;
}

void board::print()
{
	for (int i = 0; i < 20; i++)
	{
		cout << endl;
		for (int j = 0; j < 12; j++)
			cout << usedCoords[i][j] << " ";
	}
}

void board::update(point* p)
{
	for (int i = 0; i < 4; i++)
	{
		usedCoords[p[i].getY()][p[i].getX()] = 1; //changed x/y
	}
}

