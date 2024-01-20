#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> 

#include "shape.h"
#include "utilities.h"
#include "board.h"

gameConfig conf; // need to be fixed mooshon help us

shape::shape(int pNum) : direction(0), rotate(1)
{
	coordinatesToShape(body, conf.coordsArr[genRand(4)]);
	if (pNum == 1)
	{
		keys = "xad";
	}
	else
	{
		keys = "mjl";
		for (int i = 0; i < 4; i++)
			body[i].setXY(body[i].getX() + gameConfig::P2OFFSET, body[i].getY());
	}

}

void shape::coordinatesToShape(point _body[4], int coords[8])
{
	for (int i = 0; i < 4; i++)
	{
		_body[i].setXY(coords[i * 2], coords[(i * 2) + 1]);
	}
}

void shape::drawShape(char ch)
{
	for (int i = 0; i < 4; i++)
	{
		body[i].draw(ch);
	}
}

bool shape::moveShape(board& b)
{
	bool res = true;
	if (CanIMove(direction, b))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].move(direction);
		}
	}
	else
		res = false;

	setDirection(0);

	return res;
}

int shape::getDirection(char key)
{
	for (int i = 0; i < 3; ++i)
	{
		if (key == keys[i])
			return i;
	}
	return -1;
}

void shape::setDirection(int dir)
{
	if (dir == 1 && this->checkLeftBorder() == false) //&& this->edged == false)
		direction = dir;
	if (dir == 2 && this->checkRightBorder() == false) //&& this->edged == false)
		direction = dir;
	if (dir == 0) //&& this->checkDownBorder() == false) //&& this->edged == false)
		direction = dir; 
	//direction = dir;
	
}

bool shape::CanIMove(int dir, board& b)
{
		for (int i = 0; i < 4; i++)
		{
			point check;
			check =  body[i];
			check.move(dir);
			if (b.existInMat(check))// check matrix
			{
				return false;
			}
		}

		return true;
}

bool shape::checkLeftBorder()
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getX() == 1 || body[i].getX() == 19)//check x
			return true;	
	}
	return false;
}

bool shape::checkRightBorder()
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getX() == gameConfig::GAME_WIDTH || body[i].getX() == gameConfig::GAME_WIDTH + 18)//check x //changed here from (GAME_WIDTH - 1) to (GAME_WIDTH)
		{
			return true;
		}
	}
	return false;
}
bool shape::checkDownBorder()
{
	for (int i = 0; i < 4; i++)
	{
		if (body[i].getY() == gameConfig::GAME_HEIGHT - 1)//check x
		{
			return true;
		}
	}
	return false;
}

point* shape::getBody()
{
	return this->body;
}

