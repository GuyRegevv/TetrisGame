#pragma once

class board
{

	int usedCoords[20][12] = { 0 };
	int offset;
public:

	board(int);

	bool existInMat(point val);
	void print(int);
	void update(point* p);
	bool isGameOver();
	bool deleteLineAndUpdate();
	void syncBoardToDisplay();




};

bool checkIfLineFull(int* arr);
void deleteLine(int* arr);
void switchLines(int* under, int* upper);




