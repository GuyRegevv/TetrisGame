#pragma once

class board
{

	int usedCoords[20][12] = { 0 };

public:

	board();

	bool existInMat(point val);
	void print();
	void update(point* p);
	bool isGameOver();
	bool deleteLineAndUpdate();
	void syncBoardToDisplay();




};

bool checkIfLineFull(int* arr);
void deleteLine(int* arr);
void switchLines(int* under, int* upper);




