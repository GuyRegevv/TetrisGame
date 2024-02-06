#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> // for rand() function
#include <ctime>   // for seeding srand()
#include <time.h>

#include "utilities.h"
#include "gameConfig.h"
#include "point.h"
#include "board.h"
#include "shape.h"

using namespace std;

int genRand(int max)
{	
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

int gameOver()
{
	setTextColor(Color::WHITE);
	gotoxy(40, 10);
	cout << " ||| game over ! ||| " << endl;
	gotoxy(40, 20);
	int input = 0;
	cout << "(0) End Game" << endl << "(1) New Game" << endl;
	cin >> input;
	return input;
}

int printMenuAndSelect()
{	
	int res;
	cout << "(1) Start a new game" << endl;
	cout << "(2) Continue a paused game" << endl;
	cout << "(8) Pause game" << endl;
	cout << "(9) EXIT" << endl;
	cin >> res;
	return res;
}

void handlePause() //pausing game until '2' is selected
{
	char check = 0;
	gotoxy(50, 10);
	cout << "Game Paused";
	fflush(stdin);
	while (true)
	{
		if (_kbhit())
			check = _getch();
		if (check == '2')
		{
			gotoxy(50, 10);
			cout << "             ";
			break;
		}
	}

	check = 0;
}

void handleFullLines(board& b1, board& b2) //wrapper function
{
	if (b1.deleteLineAndUpdate())
		b1.syncBoardToDisplay();

	if (b2.deleteLineAndUpdate())
		b2.syncBoardToDisplay();
}

int handleGameOver(board& b1, board& b2) //wrapper function
{
	setTextColor(Color::WHITE);
	if (b1.isGameOver())
		return gameOver();

	if (b2.isGameOver())
		return gameOver();

	return 2;
}

int handleGameStart() //menu selection and drawing borders
{
	int startingKey;
	startingKey = printMenuAndSelect();
	clrscr();

	drawBorder(gameConfig::P1OFFSET);
	drawBorder(gameConfig::P2OFFSET);

	return startingKey;
}

void handleDrawing(shape& s1, shape& s2)
{
	s1.drawShape();
	s2.drawShape();
	Sleep(100);
	s1.drawShape(' ');
	s2.drawShape(' ');
}

