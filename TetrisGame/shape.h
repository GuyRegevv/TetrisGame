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

public:

	shape(int pNum);

	void drawShape();
	void drawShape(char ch);
	bool moveShape(board& b);
	void coordinatesToShape(point body[4], int coords[8]);
	int getDirection(char key);
	void setDirection(int dir);
	bool checkLeftBorder();
	bool checkRightBorder();
	bool CanIMove(int dir, board& b);
	point* getBody();
	void rotateShape();
	char getSymbol() const { return symbol; }


};