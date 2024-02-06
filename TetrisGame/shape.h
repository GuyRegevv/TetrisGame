#pragma once

#include "point.h"
#include "board.h"

class shape
{
	point body[4];
	int coordinates[8];
	int rotate;
	int direction;
	Color c;
	char symbol;

public:

	shape();

	void drawShape();
	void drawShape(char ch);
	bool moveShape(board& b);
	void coordinatesToShape(point body[4], int coords[8]);
	int getDirection(char key);
	void setDirection(int dir);
	bool checkLeftBorder();
	bool checkRightBorder();
	bool checkDownBorder();
	bool CanIMove(int dir, board& b);
	point* getBody();
	void rotateShape();




	enum type { O, I, J, L, S, Z, T };
};




/*	int O_blockCoordinates[8] = {6,1,6,2,7,1,7,2};
	int I_blockCoordinates[8] = { 5,1,6,1,7,1,8,1 };
	int J_blockCoordinates[8] = { 5,1,5,2,5,2,7,2 };
	int L_blockCoordinates[8] = { 5,2,6,2,7,2,7,1 };
	int S_blockCoordinates[8] = { 5,2,6,2,6,1,7,1 };
	int Z_blockCoordinates[8] = { 5,1,6,1,6,2,7,2 };
	int T_blockCoordinates[8] = { 5,1,6,1,6,2,7,1 }; */