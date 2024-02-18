#pragma once

#include "point.h"
#include "board.h"
#include "color.h"

// shape class is representing a single shape.
// every diffrent shape is being made from an int array of coordinates, 
// then its converted to a points array.
// for exmaple: first and second values are the x,y of first point in shape body

class shape
{
	point body[4];
	int coordinates[8];
	string keys;
	int rotate;
	int direction;
	Color c;
	char symbol;

	friend bool isFitted(const board& b, const shape& s);

public:

	shape(int pNum);
	point* getBody();
	void drawShape();
	void rotateShape();
	bool checkLeftBorder();
	void drawShape(char ch);
	bool checkRightBorder();
	bool moveShape(board& b);
	shape(const shape& other);
	int getDirection(char key);
	void setDirection(int dir);
	void moveShapeUpBy(int diff);
	void updateBody(point* newBody);
	bool CanIMove(int dir, board& b);
	void stickShapeToLeftBorder(board b);
	void stickShapeToBottomBorder(board b);
	char getSymbol() const { return symbol; }
	void coordinatesToShape(point body[4], int coords[8]);

	shape& operator=(const shape& other)
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
};