#pragma once

#include "point.h"

class shape;
class board;

void gotoxy(int x, int y);
void clrscr();
int genRand(int top);
void drawBorder(int offset);
void gameOver();
int printMenuAndSelect();
void handlePause();
void handleFullLines(board& b1, board& b2);
void handleGameOver(board& b1, board& b2);
int handleGameStart();
void handleDrawing(shape& s1, shape& s2);

