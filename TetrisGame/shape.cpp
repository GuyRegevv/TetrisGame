#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> 

#include "shape.h"
#include "utilities.h"
#include "board.h"
#include "color.h"

gameConfig conf;

//constructor, every new shape gets a random color and shape.
//the shape gets the keys controling it and ajdusting to current position (P1/P2)
shape::shape(int pNum) : direction(3), rotate(1) 
{
	setTextColor((Color)(1 + genRand(14)));
	coordinatesToShape(body, conf.coordsArr[genRand(7)]);
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


void shape::coordinatesToShape(point _body[4], int coords[8]) //converting int coordinates array to points array.
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

// making sure that the next move is legal, 
// one case for moving the shape one time for L/R keys,
// other case moving until it cant move for DROP key.
bool shape::moveShape(board& b) 
{
	bool res = true;
	if (direction == 0)
	{
		while (CanIMove(3, b))
		{
			for (int i = 0; i < 4; i++)
			{
				body[i].move(3);
			}
		}
	}

	else if (CanIMove(direction, b))
	{
		for (int i = 0; i < 4; i++)
		{
			body[i].move(direction);
		}
	}

	else
		res = false;

	setDirection(3); // was 0

	return res;
}

int shape::getDirection(char key) //converting keys controls string to directions
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
	if (dir == 1 && this->checkLeftBorder() == false)
		direction = dir;
	if (dir == 2 && this->checkRightBorder() == false) 
		direction = dir;
	if (dir == 0 || dir ==3) 
		direction = dir; 	
}

bool shape::CanIMove(int dir, board& b) //checks if the place we want to move to, is free in the board matrix.
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
		if (body[i].getX() == gameConfig::GAME_WIDTH || body[i].getX() == gameConfig::GAME_WIDTH + 18)
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
