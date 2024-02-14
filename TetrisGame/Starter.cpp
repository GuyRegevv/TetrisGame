#pragma once
#include "Starter.h"

#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch
#include <stack>

#include "gameConfig.h"
#include "utilities.h"
#include "point.h"
#include "shape.h"
#include "board.h"
#define CURRENT_GAME 2
using namespace std;



int Starter::lunch()
{
	{/*
		srand(time(0));
		board b(1);
		shape s(1);
		for (int i = 0; i < 4; i++)
			cout << s.getBody()[i].getX() << "," << s.getBody()[i].getY() << endl;
		
		s.stickShapeToBottomBorder(b);
		
		cout << "-----------------------------" << endl;
		for (int i = 0; i < 4; i++)
			cout << s.getBody()[i].getX() << ","<< s.getBody()[i].getY() << endl;
		s.stickShapeToLeftBorder(b);
		cout << "-----------------------------" << endl;
		for (int i = 0; i < 4; i++)
			cout << s.getBody()[i].getX() << "," << s.getBody()[i].getY() << endl;
	exit(1);*/
	}

	srand(time(0));
	char key = 0; //Setting Defult direction - Down
	int dir;
	int newGame = CURRENT_GAME;
	int startingKey = handleGameStart(); //Menu presentetion and selection
	//creating 2 new boards
	board b1(1);
	board b2(2);
	// bool flags to indicate when a shape finished its turn, and a new one needs to be created.
	bool currentshape1 = true;
	bool currentshape2 = true;

	if (startingKey == 8)
	{
		handleInstructions();
		startingKey = 1;
	}
	//game starts
	if (startingKey == 1)
	{
		b1.typeInput(1);
		b2.typeInput(2);
		clrscr();
		drawBorder(gameConfig::P1OFFSET);
		drawBorder(gameConfig::P2OFFSET);

		do {
			//two new shapes created. for each round
			shape s1(1);
			shape s2(2);
			currentshape1 = true;
			currentshape2 = true;
			
			//returns the moves stack
			stack<int> compMoves1;
			stack<int> compMoves2;
			updateCompMoves(b1, compMoves1, s1);
			updateCompMoves(b2, compMoves2, s2);

			//function for moves string -------------------------
			while (currentshape1 || currentshape2)
			{
				fflush(stdin);
				if (_kbhit())
					key = _getch();
				//exit game when selecting 9
				if (key == '9')
				{
					gotoxy(40, 10);
					setTextColor((Color)(15));
					cout << " ||| game over ! ||| " << endl;
					gotoxy(40, 25);
					exit(1);
					//gameOver();
				}
				//pausing game when selecting 8, resuming when selecting 2	
				else if (key == '2')
				{
					handlePause();
					key = 0;
				}
				else if (key == '8')
				{
					handleInstructions();
					key = 0;
				}
				else if (key == '5')
				{
					b1.bestMove(s1);
					Sleep(7000000);
					key = 0;
				}
				else
				{
					//setting direction according to selected key, and moving coordinates.
					if (b1.getPlayerType() == 'h')
					{
						if ((dir = s1.getDirection(key)) != -1)
						{
							s1.setDirection(dir);
							currentshape1 = s1.moveShape(b1);
						}
					}
					else
					{
						if (!compMoves1.empty())
						{
							dir = compMoves1.top();
							compMoves1.pop();
							s1.setDirection(dir);
							currentshape1 = s1.moveShape(b1);
						}
					}

					if (b2.getPlayerType() == 'h')
					{
						if ((dir = s2.getDirection(key)) != -1)
						{
							s2.setDirection(dir);
							currentshape1 = s2.moveShape(b2);
						}
					}
					else
					{
						if (!compMoves2.empty())
						{
							dir = compMoves2.top();
							compMoves2.pop();
							s2.setDirection(dir);
							currentshape1 = s2.moveShape(b2);
						}
					}

					//drawing shapes
					handleDrawing(s1, s2);
					//as long as nothing being pressed, shapes are moving down.
					currentshape1 = s1.moveShape(b1);
					currentshape2 = s2.moveShape(b2);
					key = 0;
					fflush(stdin);
				}
			}

			//end of round,
			// updating the board matrix
			b1.update(s1);
			b2.update(s2);
			//drawing the shapes in the place they landed
			if (s1.getSymbol() != '@')
				s1.drawShape();
			if (s2.getSymbol() != '@')
				s2.drawShape();
			//check for full lines and delete.
			handleFullLines(b1, b2);
			//check if game is over
			newGame = handleGameOver(b1, b2);


		} while (key != '9' && newGame == CURRENT_GAME);

		return newGame;
	}
	
	return 0;
}



