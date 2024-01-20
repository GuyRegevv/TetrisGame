#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> // for rand() function
#include <ctime>   // for seeding srand()

#include "utilities.h"
#include "gameConfig.h"
#include "point.h"
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

void drawBorder(int offset)
{
	for (int col = 0; col <= gameConfig::GAME_WIDTH + 1; col++)
	{
		gotoxy(col + offset, 0);
		cout << '-';

		gotoxy(col + offset, gameConfig::GAME_HEIGHT + 1);
		cout << '-';
	}

	for (int row = 0; row <= gameConfig::GAME_HEIGHT + 1; row++)
	{
		gotoxy(offset, row);
		cout << '|';

		gotoxy(gameConfig::GAME_WIDTH + 1 + offset, row);
		cout << '|';
	}

}

void gameOver()
{
	gotoxy(40, 10);
	cout << " ||| game over bish! ||| ";
	gotoxy(40, 20);
	exit(1);
}
int printMenuAndSelect()
{	
	int res;
	cout << "(1) Start a new game" << endl;
	cout << "(2) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
	cin >> res;
	return res;
}