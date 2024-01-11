#pragma once

#include "point.h"

class shape
{
	point body[4];
	int coordinates[8];
	int rotate;
	int direction;

public:

	shape();

	void drawShape(char ch);
	void moveShape(int direction);
	void coordinatesToShape(point body[4], int coords[8]);
};

	//int color;
	//int type;


/*	int O_blockCoordinates[8] = {6,1,6,2,7,1,7,2};
	int I_blockCoordinates[8] = { 5,1,6,1,7,1,8,1 };
	int J_blockCoordinates[8] = { 5,1,5,2,5,2,7,2 };
	int L_blockCoordinates[8] = { 5,2,6,2,7,2,7,1 };
	int S_blockCoordinates[8] = { 5,2,6,2,6,1,7,1 };
	int Z_blockCoordinates[8] = { 5,1,6,1,6,2,7,2 };
	int T_blockCoordinates[8] = { 5,1,6,1,6,2,7,1 }; */

