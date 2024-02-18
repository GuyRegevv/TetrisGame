#pragma once
#include <vector>
#include "optionalMove.h"
// board class represents the game map progress.
// a matrix in the size of the game board
// 0 for empty space and 1 for used space.
// changes in the game are managed here, then syncing for printing

class shape;

class board
{
	int usedCoords[20][12] = { 0 };
	int offset;
	char pType; 
	friend void bombExplotion(point* p, board& b);

public:

	board(int);

	void print() const;
	void update(shape& s);
	bool isGameOver() const;
	void typeInput(int pNum);
	void syncBoardToDisplay();
	bool deleteLineAndUpdate();
	optionalMove bestMove(shape& s);
	bool existInMat(point val) const;
	void deleteShapeFromBoard(shape& s);
	int getOffset() const { return offset; }
	void setPlayerType(char c) { pType = c; }
	void handleFullLines(board& b1, board& b2);
	void setType(int _pType) { pType = _pType; }
	char getPlayerType() const { return pType; }
	bool isFitted(const board& b, shape& s) const;
	vector <optionalMove> findPossibleMoves(shape& s);
	vector <optionalMove> movesThatDeleteLines(vector<optionalMove> posMovesArr);

	board& operator=(const board& other)
	{
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 12; j++)
				usedCoords[i][j] = other.usedCoords[i][j];


		offset = other.getOffset();

		return *this;
	}
};

bool checkIfLineFull(int* arr);
void deleteLine(int* arr);
void switchLines(int* under, int* upper);
void bombExplotion(point* p, board& b);





