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
shape::shape(int pNum) : direction(3), symbol('#')
{
	setTextColor((Color)(1 + genRand(14)));
	if (genRand(50) == 9)
	{
		coordinatesToShape(body, conf.BOMB_blockCoordinates);
		symbol = '@';
	}
	else 
		coordinatesToShape(body, conf.coordsArr[genRand(7)]);
	if (pNum == 1)
	{
		keys = "xads";
	}
	else
	{
		keys = "mjlk";
		for (int i = 0; i < 4; i++)
			body[i].setXY(body[i].getX() + gameConfig::P2OFFSET, body[i].getY());
	}
}

shape::shape(const shape& other)
{
	for (int i = 0; i < 4; i++)
	{
		body[i] = other.body[i];
	}
	keys = other.keys;
	rotate = other.rotate;
	direction = other.direction;
	c = other.c;
	symbol = other.symbol;

}


void shape::coordinatesToShape(point _body[4], int coords[8]) //converting int coordinates array to points array.
{
	for (int i = 0; i < 4; i++)
	{
		_body[i].setXY(coords[i * 2], coords[(i * 2) + 1]);
	}
}

void shape::drawShape()
{
	for (int i = 0; i < 4; i++)
	{
		body[i].draw(symbol);
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
	for (int i = 0; i < 4; ++i)
	{
		if (key == keys[i])
		{
			if (i == 3)
			{
				rotateShape();
			}
			return i;
		}
	}
	return -1;
}

void shape::rotateShape()
{
	int size = 4;
	// Find the center point of the shape
	int centerX = 0, centerY = 0;
	for (int i = 0; i < size; ++i) {
		centerX += body[i].getX();
		centerY += body[i].getY();
	}
	centerX /= size;
	centerY /= size;

	// Rotate the shape around its center
	for (int i = 0; i < size; ++i) {
		// Translate coordinates relative to center
		int relX = body[i].getX() - centerX;
		int relY = body[i].getY() - centerY;

		// Rotate 90 degrees clockwise
		int newX = centerX + relY;
		int newY = centerY - relX;

		// Update the shape with new coordinates
		body[i].setX(newX);
		body[i].setY(newY);
	}
}

void shape::setDirection(int dir)
{
	if (dir == 1 && this->checkLeftBorder() == false)
		direction = dir;
	if (dir == 2 && this->checkRightBorder() == false) 
		direction = dir;
	if (dir == 0 || dir ==3) 
		direction = dir; 	
	//if(dir==4)
	//rotate
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
void shape::stickShapeToLeftBorder(board b)
{
		setDirection(1);
		while (moveShape(b))
		{
			setDirection(1);

		}
		b.update(*this);

}
void shape::stickShapeToBottomBorder(board b)
{
	setDirection(3);
	while (moveShape(b))
	{
	}
	b.update(*this);

}

void shape::moveShapeUpBy(int diff)
{
	int currY = 0;
	for (int i = 0; i < 4; i++)
	{
		currY = body[i].getY();
		body[i].setY(currY + diff);
	}
}

void shape::updateBody(point* newBody)
{
	for (int i = 0; i < 4; i++)
		body[i] = newBody[i];
}


