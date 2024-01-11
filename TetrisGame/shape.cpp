#include "shape.h"
#include "utilities.h"

#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> 


gameConfig conf; // need to be fixed mooshon help us

shape::shape() : direction(1), rotate(1)
{
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

void shape::moveShape()
{
	for (int i = 0; i < 4; i++)
	{
		body[i].move(direction);
	}
}

int shape::getDirection(char key)
{
	for (int i = 0; i < 3; ++i)
	{
		if (key == conf.p1Keys[i])
			return i;
	}
	return -1;
}

void shape::setDirection(int dir) 
{
	direction = dir;
}
