#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <cstdlib> // for rand() function
#include <ctime>   // for seeding srand()
#include <time.h>
#include <vector>
#include <stack>

#include "utilities.h"
#include "gameConfig.h"
#include "point.h"
#include "board.h"
#include "shape.h"
#include "optionalMove.h"

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
	gotoxy(40, 12);
	cout << "(0) End Game " << "(1) New Game" << endl;
	gotoxy(40, 13);
	int input = 0;
	cin >> input;
	gotoxy(40, 20);
	return input;
}

int printMenuAndSelect()
{	
	int res;
	cout << "(1) Start a new game - Human vs Human" << endl;
	cout << "(2) Start a new game - Human vs Computer" << endl;
	cout << "(3) Start a new game - Computer vs Computer" << endl;
	cout << "(4) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
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
		if (check == '4')
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

	return startingKey;
}

void handleDrawing(shape& s1, shape& s2)
{
	s1.drawShape();
	s2.drawShape();
	Sleep(400);
	s1.drawShape(' ');
	s2.drawShape(' ');
}

void handleInstructions()//display instructions until its being realse by '8'
{
	char check = 0;
	setTextColor((Color)(15));
	//prints rules in {} 
	{
		gotoxy(40, 10);
		cout << "Rules:" << endl;
		gotoxy(40, 11);
		cout << "Players take turns controlling falling tetrominoes on their respective boards." << endl;
		gotoxy(40, 12);
		cout << "The goal is to complete horizontal lines by filling them with tetrominoes." << endl;
		gotoxy(40, 13);
		cout << "Completed lines disappear, and players score points for each line cleared." << endl;
		gotoxy(40, 14);
		cout << "The game ends if a tetromino reaches the top of the board." << endl;
		gotoxy(40, 15);
		cout << "Player 1 Controls:" << endl;
		gotoxy(40, 16);
		cout << "A: Move tetromino left." << endl;
		gotoxy(40, 17);
		cout << "D : Move tetromino right." << endl;
		gotoxy(40, 18);
		cout << "S : Rotate tetromino." << endl;
		gotoxy(40, 19);
		cout << "X : Drop tetromino instantly." << endl;
		gotoxy(40, 20);
		cout << "Player 2 Controls:" << endl;
		gotoxy(40, 21);
		cout << "J: Move tetromino left." << endl;
		gotoxy(40, 22);
		cout << "L : Move tetromino right." << endl;
		gotoxy(40, 23);
		cout << "K : Rotate tetromino." << endl;
		gotoxy(40, 24);
		cout << "M : Drop tetromino instantly." << endl;
	}
	fflush(stdin);
	while (true)
	{
		if (_kbhit())
			check = _getch();
		if (check == '8')
		{
			gotoxy(40, 10);
			cout << "                     " << endl;
			gotoxy(40, 11);
			cout << "                                                                               " << endl;
			gotoxy(40, 12);
			cout << "                                                                               " << endl;
			gotoxy(40, 13);
			cout << "                                                                               " << endl;
			gotoxy(40, 14);
			cout << "                                                                               " << endl;
			gotoxy(40, 15);
			cout << "                                                                               " << endl;
			gotoxy(40, 16);
			cout << "                                                                               " << endl;
			gotoxy(40, 17);
			cout << "                                                                               " << endl;
			gotoxy(40, 18);
			cout << "                                                                               " << endl;
			gotoxy(40, 19);
			cout << "                                                                               " << endl;
			gotoxy(40, 20);
			cout << "                                                                               " << endl;
			gotoxy(40, 21);
			cout << "                                                                               " << endl;
			gotoxy(40, 22);
			cout << "                                                                               " << endl;
			gotoxy(40, 23);
			cout << "                                                                               " << endl;
			gotoxy(40, 24);
			cout << "                                                                               " << endl;

			break;
		}
	}

	

}

optionalMove lowestMove(vector <optionalMove> moves)
{
	int lowestY = 0;
	optionalMove res;
	for (const auto& m : moves)
	{
		for (int i = 0; i < 4; i++)
		{
			if (m.getDestination()[i].getY() > lowestY)
			{
				lowestY = m.getDestination()[i].getY();
				res = m;
			}
		}
	}

	return res;
}

stack<int> computerMoves(shape& origin, optionalMove move)
{	
	point* dest = move.getDestination();
	int widthDiff = 0;
	int originX = origin.getBody()[0].getX();
	int destX = dest[0].getX();
	stack<int> moves;

	widthDiff = originX - destX;

	if (widthDiff < 0)
		for (int i = 0; i < widthDiff * -1; i++)
			moves.push(2);
	if (widthDiff > 0)
		for (int i = 0; i < widthDiff; i++)
			moves.push(1);
	
	for (int i = 0; i < move.getNumOfRotations(); i++)
		moves.push(3);

	return moves;
}

void updateCompMoves(board& b1, stack<int>& stack1, shape& shape1)
{
	board dummyBoard(1);
	dummyBoard = b1;
	if (shape1.getSymbol() == '@')
		return;
	if (b1.getPlayerType() == 'c')
	{
		optionalMove compBestMove;
		//compBestMove = b1.bestMove(shape1);
		compBestMove = dummyBoard.bestMove(shape1);
		stack1 = computerMoves(shape1, compBestMove);
	}
}

char setComputerLevel()
{
	char res;
	cout << "Please choose computer level" << endl;
	cout << "(a) BEST (b) GOOD and (c) NOVICE" << endl;
	cin >> res;
	return res;

}