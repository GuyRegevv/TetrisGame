#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> // for rand() function
#include <ctime>   // for seeding srand()

#include "utilities.h"
#include "gameConfig.h"

using namespace std;

int genRand(int max)
{
	srand(time(0));
	return (rand() % max);
}


void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// function definition -- requires process.h
void clrscr()
{
	system("cls");
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
