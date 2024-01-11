#include "shape.h"
#include "utilities.h"

#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> 

shape::shape() : direction(1), rotate(1)
{
	gameConfig conf;
	coordinatesToShape(body, conf.coordsArr[genRand(7)]);
}

void shape::coordinatesToShape(point _body[4], int coords[8])
{
	for (int i = 0; i < 4; i++)
	{
		_body[i].setXY(coords[i*2], coords[(i*2) + 1]);
	}
}

void shape::drawShape(char ch)
{
	for (int i = 0; i < 4; i++)
	{
		body[i].draw(ch);
	}
}

void shape::moveShape(int direction)
{
	for (int i = 0; i < 4; i++)
	{
		body[i].move(direction);
	}
}
