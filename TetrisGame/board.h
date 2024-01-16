#pragma once

class board
{

	int usedCoords[20][12] = { 0 };

public:

	board();

	bool existInMat(point val);
	void print();
	void update(point* p);



};

