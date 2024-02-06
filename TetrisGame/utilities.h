#pragma once

#include "point.h"

//utilitis contains all kind of functions without a direct relation to certain objects, and wrapper functions.

class shape;
class board;

void gotoxy(int x, int y);
void clrscr();
int genRand(int top);
void drawBorder(int offset);
int gameOver();
int printMenuAndSelect();
void handlePause();
void handleFullLines(board& b1, board& b2);
int handleGameOver(board& b1, board& b2);
int handleGameStart();
void handleDrawing(shape& s1, shape& s2);

