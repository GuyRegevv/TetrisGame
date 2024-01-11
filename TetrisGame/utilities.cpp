#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> // for rand() function
#include <ctime>   // for seeding srand()

#include "utilities.h"

using namespace std;

int genRand(int top)
{
	srand(time(0));
	return (rand() % top);
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
