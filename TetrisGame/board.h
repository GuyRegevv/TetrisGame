#pragma once
#include <vector>
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

	bool existInMat(point val) const;
	void print(int) const;
	void update(shape& s);
	bool isGameOver() const;
	bool deleteLineAndUpdate();
	void syncBoardToDisplay();
	void handleFullLines(board& b1, board& b2);
	int getOffset() const { return offset; }
	point* bestMove(shape& s) ;
	bool isFitted(const board& b, shape& s) const;
	void deleteShapeFromBoard(shape& s);
	vector <point*> movesThatDeleteLines(vector <point*> points);
	vector <point*> findPossibleMoves(shape& s);
	void setPlayerType(char c) { pType = c; }
	char getPlayerType() const { return pType; }
	void typeInput(int pNum);




};

bool checkIfLineFull(int* arr);
void deleteLine(int* arr);
void switchLines(int* under, int* upper);
void bombExplotion(point* p, board& b);





