#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch

#include "gameConfig.h"
#include "utilities.h"
#include "point.h"
#include "shape.h"

using namespace std;

void drawBorder();

int main()
{
	drawBorder();

	point p(6, 1);
	shape s;

	while (!_kbhit())
	{
		s.drawShape('#');
		Sleep(500);
		s.drawShape(' ');
		s.moveShape(1);
	}

	//more thigs to check

}

void drawBorder()
{
	for (int col = 0; col <= gameConfig::GAME_WIDTH + 1; col++)
	{
		gotoxy(col, 0);
		cout << '-';

		gotoxy(col, gameConfig::GAME_HEIGHT + 1);
		cout << '-';
	}

	for (int row = 0; row <= gameConfig::GAME_HEIGHT + 1; row++)
	{
		gotoxy(0, row);
		cout << '|';

		gotoxy(gameConfig::GAME_WIDTH + 1, row);
		cout << '|';
	}

}

