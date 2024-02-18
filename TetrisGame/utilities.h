#pragma once

#include "point.h"
#include "optionalMove.h"
#include <vector>
#include <stack>

//utilitis contains all kind of functions without a direct relation to certain objects, and wrapper functions.

class shape;
class board;

void clrscr();
int gameOver();
void handlePause();
int genRand(int top);
int handleGameStart();
char setComputerLevel();
int printMenuAndSelect();
void gotoxy(int x, int y);
void handleInstructions();
void drawBorder(int offset);
int lowestYinMove(optionalMove opt);
int highestYinMove(optionalMove opt);
void handleDrawing(shape& s1, shape& s2);
int handleGameOver(board& b1, board& b2);
void handleFullLines(board& b1, board& b2);
optionalMove lowestMove(vector<optionalMove> moves);
optionalMove highestMove(vector <optionalMove> moves);
stack<int> computerMoves(shape& origin, optionalMove dest);
void updateCompMoves(board& b1, stack<int>& stack1, shape& shape1, char computerLevel);




