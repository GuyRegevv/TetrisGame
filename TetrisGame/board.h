#pragma once

// board class represents the game map progress.
// a matrix in the size of the game board
// 0 for empty space and 1 for used space.
// changes in the game are managed here, then syncing for printing

class board
{
	int usedCoords[20][12] = { 0 };
	int offset;
public:

	board(int);

	bool existInMat(point val) const;
	void print(int) const;
	void update(point* p);
	bool isGameOver() const;
	bool deleteLineAndUpdate();
	void syncBoardToDisplay();
	void handleFullLines(board& b1, board& b2);


};

bool checkIfLineFull(int* arr);
void deleteLine(int* arr);
void switchLines(int* under, int* upper);




