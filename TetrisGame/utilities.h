#pragma once

#include "point.h"



void gotoxy(int x, int y);
void clrscr();
int genRand(int top);
void drawBorder(int offset);
void gameOver();
int printMenuAndSelect();